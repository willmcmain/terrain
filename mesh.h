#ifndef __MESH_H__
#define __MESH_H__
#include <GL/glew.h>
#include "shader.h"

struct wlVertex {
    GLfloat position[3];
};

class wlMesh {
    public:
             wlMesh(const int count, const wlShader* shader);
             wlMesh(wlVertex* data, const int count, const wlShader* shader);
            ~wlMesh();
        void bind_values();
        void draw();
    private:
        int             count;
        wlVertex*       data;
        const wlShader* shader;
        GLuint          vbo;
};
#endif
