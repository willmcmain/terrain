#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "shader.h"
#include "mesh.h"

class wlRenderer {
    public:
             wlRenderer(const wlShader*);
        void set_shader(const wlShader*);
        void render() const;
        void add_mesh(wlMesh*);
    private:
        const wlShader* shader;
        wlMesh** meshes;
        int mesh_count;
        int mesh_max;
};

#endif
