#version 330 core

void main() {
    if (gl_FragCoord.x < 250.0) {
        gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}
