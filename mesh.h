#ifndef __MESH_H__
#define __MESH_H__
#include <GL/glew.h>
#include "shader.h"

struct wlVertex {
    GLfloat position[3];
};

struct wlShaderVars {
    GLuint position;
};

class wlMesh {
    public:
             wlMesh(const int count, const wlShader* shader);
             wlMesh(wlVertex* data, const int count, const wlShader* shader);
            ~wlMesh();
        void render();
    private:
        int             count;
        wlVertex*       data;
        const wlShader* shader;
        wlShaderVars    shader_vars;
        GLuint          vbo;
};
#endif
