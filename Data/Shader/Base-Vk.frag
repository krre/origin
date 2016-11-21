#version 430 core

out vec3 fragColor;

layout(std140, binding = 0) uniform buf {
    uniform vec3 color;
} ubuf;

void main() {
    fragColor = ubuf.color;
}
