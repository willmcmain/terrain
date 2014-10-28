#ifndef __UTILS_H__
#define __UTILS_H__
#include <GL/glew.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static GLfloat* perspective_matrix(
        GLfloat view_angle,
        GLfloat aspect_ratio,
        GLfloat z_near,
        GLfloat z_far) {
    GLfloat* matrix = (GLfloat*)malloc(sizeof(GLfloat)*16);
    matrix[0] = 1.0 / tan(view_angle);
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;

    matrix[4] = 0.0;
    matrix[5] = aspect_ratio / tan(view_angle);
    matrix[6] = 0.0;
    matrix[7] = 0.0;

    matrix[8]  = 0.0;
    matrix[9]  = 0.0;
    matrix[10] = (z_far + z_near) / (z_far - z_near);
    matrix[11] = 1.0;

    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = -2.0 * z_far * z_near / (z_far - z_near);
    matrix[15] = 0.0;
    return matrix;
}

static void print_matrix(const GLfloat* matrix) {
    for(int y=0; y < 4; y++) {
        for(int x=0; x < 4; x++) {
            printf("%f ", matrix[y*4 + x]);
        }
        printf("\n");
    }
}
#endif
