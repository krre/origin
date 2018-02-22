#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

layout (std140, binding = 0) uniform UBO {
    mat4 mvp;
} ubo;

layout (location = 0) out vec4 outColor;

void main() {
    outColor = color;
    gl_Position = ubo.mvp * position;
    gl_Position.y = -gl_Position.y; // TODO: Use #define GLM_FORCE_LEFT_HANDED before include glm
}
