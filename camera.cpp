#include "camera.h"
#include <math.h>
#include <glm/glm.hpp>
const float TWOPI = 6.283185307179586;

/* ==========
 * set_pos
 * ========== */
void wlCamera::set_pos(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

/* ==========
 * move
 * ========== */
void wlCamera::move(float x, float y, float z) {
    position[0] += x;
    position[1] += y;
    position[2] += z;
}

/* ==========
 * rotate
 * ========== */
void wlCamera::rotate(float x, float y) {
    xrot += fmod(x, TWOPI);
    yrot += fmod(y, TWOPI);
}

/* ==========
 * set_rot
 * ========== */
void wlCamera::set_rot(float x, float y) {
    xrot = fmod(x, TWOPI);
    yrot = fmod(y, TWOPI);
}
