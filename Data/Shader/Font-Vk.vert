#version 430 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 texCoords;

layout(std140, binding = 0) uniform buf {
    mat4 projection;
} ubuf;

void main() {
    gl_Position = ubuf.projection * vec4(vertex.xy, 0.0, 1.0);
    texCoords = vertex.zw;
}
