#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "shader.h"

using namespace std;

/* ===========
 * constructor
 * =========== */
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

    vars.position = glGetAttribLocation(this->program, "position");
    vars.projection = glGetUniformLocation(this->program, "projection");
    vars.view = glGetUniformLocation(this->program, "view");
    vars.camera = glGetUniformLocation(this->program, "camera");
}


/* =========
 * read_file
 * ========= */
wlShaderVars wlShader::get_vars() const {
    return vars;
}


/* =========
 * read_file
 * ========= */
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


/* =========
 * read_file
 * ========= */
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
