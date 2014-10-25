#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

/* ===========
 * constructor
 * =========== */
wlRenderer::wlRenderer(const wlShader* shader) {
    this->shader = shader;
    glUseProgram(shader->program);

    mesh_count = 0;
    mesh_max = 4;
    meshes = (wlMesh**)malloc(sizeof(wlMesh)*mesh_max);
}


/* ==========
 * set_shader
 * ========== */
void wlRenderer::set_shader(const wlShader* shader) {
    this->shader = shader;
    glUseProgram(shader->program);
}


/* ==========
 * add_mesh
 * ========== */
void wlRenderer::add_mesh(wlMesh* mesh) {
    if(mesh_count == mesh_max) {
        fprintf(stderr, "Mesh thingy is full, mesh not added\n");
        return;
    }
    meshes[mesh_count] = mesh;
    mesh_count++;
}


/* ======
 * render
 * ====== */
void wlRenderer::render() const {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < mesh_count; i++) {
        meshes[0]->draw();
    }
}
