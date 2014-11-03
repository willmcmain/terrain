#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "shader.h"
#include "mesh.h"
#include "camera.h"

class wlRenderer {
    public:
             wlRenderer(const wlShader*);
        void set_shader(const wlShader*);
        void render() const;
        void add_mesh(wlMesh*);
        void set_projection(const GLfloat* matrix);
        void set_view(const GLfloat* matrix);
        wlCamera camera;
    private:
        const wlShader* shader;
        wlMesh**        meshes;
        int             mesh_count;
        int             mesh_max;
        GLfloat         projection[16];
        GLfloat         view[16];
};

#endif
