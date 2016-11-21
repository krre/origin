#version 430 core

in vec2 texCoords;
out vec4 color;

layout(std140, binding = 0) uniform UBO {
    vec3 textColor;
} ubo;

uniform sampler2D text;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    color = vec4(ubo.textColor, 1.0) * sampled;
}
