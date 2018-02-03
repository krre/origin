#version 450 core

layout (location = 0) in vec3 position;

layout (std140, binding = 0) uniform UBO {
    mat4 mvp;
} uboVert;

void main() {
    gl_Position = uboVert.mvp * vec4(position, 1.0);
}
