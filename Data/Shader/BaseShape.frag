#version 450 core

layout(binding = 1) uniform sampler2D samplerImage;

layout (location = 0) in struct {
    vec2 uv;
    vec4 color;
} inUVColor;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = inUVColor.color;
}
