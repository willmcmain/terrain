#include <stdlib.h>
#include <stddef.h>
#include "mesh.h"
/* ==================
 * wlMesh constructor
 * ================== */
wlMesh::wlMesh(const int count, const wlShader* shader) {
    this->count = count;
    this->shader = shader;
    this->data = (wlVertex*)malloc(sizeof(wlVertex)*count);

    // Create buffers
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Get shader variables
    shader_vars.position = glGetAttribLocation(shader->program, "position");
}

wlMesh::wlMesh(wlVertex* data, const int count, const wlShader* shader) {
    this->data = data;
    this->count = count;
    this->shader = shader;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wlVertex)*count, data,
        GL_STATIC_DRAW);

    shader_vars.position = glGetAttribLocation(shader->program, "position");
}


/* ==================
 * wlMesh destructor
 * ================== */
wlMesh::~wlMesh() {
    free(this->data);
}


/* ===========
 * render mesh
 * =========== */
void wlMesh::render() {
    glUseProgram(shader->program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        shader_vars.position,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(wlVertex),
        (void*)0
        //(void*)offsetof(wlVertex, position)
    );
    glEnableVertexAttribArray(shader_vars.position);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glDisableVertexAttribArray(shader_vars.position);
}
