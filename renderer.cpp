#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "utils.h"

/* ===========
 * constructor
 * =========== */
wlRenderer::wlRenderer(const wlShader* shader) {
    this->shader = shader;
    glUseProgram(shader->program);

    mesh_count = 0;
    mesh_max = 4;
    meshes = (wlMesh**)malloc(sizeof(wlMesh)*mesh_max);

    GLfloat identity[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    memcpy(&view, &identity, 16);
    memcpy(&projection, &identity, 16);
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

/* ===============
 * set_perspective
 * =============== */
void wlRenderer::set_projection(const GLfloat* matrix) {
    memcpy(&projection, matrix, sizeof(GLfloat)*16);
}

/* ===============
 * set_view
 * =============== */
void wlRenderer::set_view(const GLfloat* matrix) {
    memcpy(&view, matrix, (sizeof(GLfloat)*16));
}

/* ======
 * render
 * ====== */
void wlRenderer::render() const {
    glUniformMatrix4fv(
        shader->get_vars().projection,
        1, GL_FALSE,
        this->projection);
    glUniformMatrix4fv(
        shader->get_vars().view,
        1, GL_FALSE,
        this->view);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < mesh_count; i++) {
        meshes[0]->draw();
    }
}
