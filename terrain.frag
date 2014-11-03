#version 110

varying vec3 vBC;

void main() {
    if(any(lessThan(vBC, vec3(0.01)))) {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else {
        gl_FragColor = vec4(0.0, 0.5, 0.0, 1.0);
        //discard;
    }
}
