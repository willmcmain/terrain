#version 110

uniform mat4 projection;
uniform mat4 view;
uniform float camera[5];

attribute vec3 position;
attribute vec3 barycentric;

varying vec3 vBC;

mat4 get_view() {
    mat4 pos = mat4(
        vec4(1.0f, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, 1.0f, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 1.0f, 0.0f),
        vec4(-camera[0], -camera[1], -camera[2], 1.0f)
    );
    mat4 xrot = mat4(
        vec4(1.0f, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, 1.0f, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 1.0f, 0.0f),
        vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    mat4 yrot = mat4(
        vec4(1.0f, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, 1.0f, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 1.0f, 0.0f),
        vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    return yrot * xrot * pos;
}

void main() {
    gl_Position = projection
                * get_view()
                * vec4(position, 1.0);

    vBC = barycentric;
}
