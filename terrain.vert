#version 110

uniform mat4 projection;
uniform mat4 view;
attribute vec3 position;

void main() {
    gl_Position = projection
                * view
                * vec4(position, 1.0);
}
