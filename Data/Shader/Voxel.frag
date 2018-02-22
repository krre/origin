#version 450 core

layout (location = 0) in struct {
    vec4 color;
} inColor;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = inColor.color;
}
