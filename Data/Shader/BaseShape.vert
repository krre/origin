#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

layout (std140, binding = 0) uniform UBO {
    mat4 mvp;
} ubo;

layout (location = 0) out struct {
    vec2 uv;
    vec4 color;
} outUVColor;

void main() {
    gl_Position = ubo.mvp * vec4(position, 0, 1);
}
