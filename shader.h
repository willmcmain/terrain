#ifndef __SHADER_H__
#define __SHADER_H__
#include <GL/glew.h>

class wlShader {
    public:
        wlShader(const char* vertex_file, const char* fragment_file);
        GLuint program;
    private:
        GLuint make_shader(GLenum type, const char* filename);
        GLuint vertex_shader;
        GLuint fragment_shader;
};
#endif
