#version 430 core

layout(location = 0) in vec3 position;

layout(std140, binding = 0) uniform UBO {
    mat4 mvp;
} ubo;

void main() {
    gl_Position = ubo.mvp * vec4(position, 1.0);
}
