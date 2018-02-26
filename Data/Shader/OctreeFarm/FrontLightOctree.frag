#version 450 core

layout (location = 0) in vec4 color;
layout (location = 1) in vec3 normal;
layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = color;
}
