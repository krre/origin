#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

layout (std140, binding = 0) uniform UBO {
    mat4 mvp;
    int shadeless;
} ubo;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out int outShadeless;

void main() {
    outColor = color;
    outShadeless = ubo.shadeless;
    outNormal = vec3(normalize(ubo.mvp * vec4(normal, 1.0)));
    gl_Position = ubo.mvp * position;
    gl_Position.y = -gl_Position.y; // TODO: Use #define GLM_FORCE_LEFT_HANDED before include glm
}
