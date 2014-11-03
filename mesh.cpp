#include <stdlib.h>
#include <stddef.h>
#include "mesh.h"
/* ===================
 * wlMesh constructor
 * =================== */
wlMesh::wlMesh(wlVertex* data, const int count, const wlShader* shader) {
    this->data = data;
    this->count = count;
    this->shader = shader;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wlVertex)*count, data,
        GL_STATIC_DRAW);
}


/* ==================
 * wlMesh destructor
 * ================== */
wlMesh::~wlMesh() {
    free(this->data);
}


/* ==================
 * bind_values
 * ================== */
void wlMesh::bind_values() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        shader->get_vars().position,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(wlVertex),
        (void*)offsetof(wlVertex, position)
    );
    glVertexAttribPointer(
        shader->get_vars().barycentric,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(wlVertex),
        (void*)offsetof(wlVertex, barycentric)
    );
}


/* ===========
 * render mesh
 * =========== */
void wlMesh::draw() {
    bind_values();
    glEnableVertexAttribArray(shader->get_vars().position);
    glEnableVertexAttribArray(shader->get_vars().barycentric);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glDisableVertexAttribArray(shader->get_vars().position);
    glDisableVertexAttribArray(shader->get_vars().barycentric);
}
