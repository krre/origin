#version 330 core

layout(location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;
uniform mat4 model;

out vec3 fragNormal;
out vec3 fragPos;

void main() {
    gl_Position = mvp * vec4(position, 1.0f);
    fragPos = vec3(model * vec4(position, 1.0f));
    fragNormal = mat3(transpose(inverse(model))) * normal;
}
