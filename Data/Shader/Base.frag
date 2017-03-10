#version 450 core

layout (location = 0) out vec4 fragColor;

layout(std140, binding = 1) uniform UBO {
    vec3 color;
} uboFrag;

void main() {
    fragColor = vec4(uboFrag.color, 1.0);
}
