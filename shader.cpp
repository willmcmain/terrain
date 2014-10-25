#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "shader.h"

using namespace std;

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    char* buffer;
    if(!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char*)malloc(length+1);
    length = fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';

    return buffer;
}


GLuint wlShader::make_shader(GLenum type, const char* filename) {
    char* source = read_file(filename);
    GLuint shader = glCreateShader(type);
    GLint shader_ok = GL_FALSE;
    GLint length = strlen(source);

    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if(!shader_ok) {
        fprintf(stderr, "Failed to compile %s\n", filename);
        glDeleteShader(shader);
        exit(1);
    }

    return shader;
}


wlShader::wlShader(const char* vertex_file, const char* fragment_file) {
    GLint program_ok;

    this->vertex_shader = make_shader(GL_VERTEX_SHADER, vertex_file);
    this->fragment_shader = make_shader(GL_FRAGMENT_SHADER, fragment_file);
    this->program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if(!program_ok) {
        fprintf(stderr, "Failed to link shader program!\n");
        glDeleteProgram(program);
        exit(1);
    }
}
