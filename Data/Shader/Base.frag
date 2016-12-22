#version 450 core

out vec3 fragColor;

layout(std140, binding = 0) uniform UBO {
    vec3 color;
} ubo;

void main() {
    fragColor = ubo.color;
}
