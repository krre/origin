#version 450 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 texCoords;

layout(std140, binding = 0) uniform UBO {
    mat4 projection;
} ubo;

void main() {
    gl_Position = ubo.projection * vec4(vertex.xy, 0.0, 1.0);
    texCoords = vertex.zw;
}
