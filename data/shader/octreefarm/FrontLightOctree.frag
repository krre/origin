#version 450 core

layout (location = 0) in vec4 color;
layout (location = 1) in vec3 normal;
layout (location = 2) in flat int shadeless;

layout (location = 0) out vec4 fragColor;

const vec3 lightPos = vec3(-0.3, 0.5, 0.8);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main() {
    if (shadeless > 0) {
        fragColor = color;
    } else {
        vec3 lightDir = normalize(lightPos);
        vec3 diffuse = max(dot(normal, lightDir), 0.0) * lightColor;
        fragColor = vec4(diffuse, 1.0) * color;
    }
}
