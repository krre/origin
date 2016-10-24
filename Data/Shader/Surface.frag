#version 330 core

in vec2 UV;
uniform sampler2D surface;

void main() {
    gl_FragColor = vec4(texture(surface, UV).rgb, 1.0);
}
