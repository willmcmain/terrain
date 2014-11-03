#ifndef __SHADER_H__
#define __SHADER_H__
#include <GL/glew.h>

struct wlShaderVars {
    GLuint position;
    GLuint barycentric;
    GLuint projection;
    GLuint view;
    GLuint camera;
};

class wlShader {
    public:
                     wlShader(const char* vert_file, const char* frag_file);
        wlShaderVars get_vars() const;
        GLuint       program;
    private:
        GLuint make_shader(GLenum type, const char* filename);
        GLuint vertex_shader;
        GLuint fragment_shader;
        wlShaderVars vars;
};
#endif
