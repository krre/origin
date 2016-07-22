#version 330 core

layout(location = 0) in vec4 position;

out vec3 fragmentColor;

uniform vec3 color;
uniform mat4 mvp;

void main() {
    gl_Position = mvp * position;
    fragmentColor = color;
}
