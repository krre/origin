#version 430 core

layout(location = 0) in vec3 position;

layout(std140, binding = 0) uniform buf {
    mat4 mvp;
} ubuf;

void main() {
    gl_Position = ubuf.mvp * vec4(position, 1.0);
}
