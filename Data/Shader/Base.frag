#version 450 core

layout (location = 0) out vec4 fragColor;

layout(std140, binding = 1) uniform UBO {
    vec3 color;
} ubo;

void main() {
    fragColor = vec4(ubo.color, 1.0);
}
