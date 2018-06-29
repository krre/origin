#version 450 core

layout(std140, binding = 0) uniform UBO {
    vec4 backgroundColor;
    vec4 lightColor;
    vec4 lightPos;

    int shadeless;
    int frameWidth;
    int frameHeight;

    float ambientStrength;
    float lod;
} ubo;

layout (std430, binding = 1) buffer Blocks {
    uint data[];
} blocks;

layout (location = 0) out vec4 fragColor;

struct Ray {
    vec3 origin;
    vec3 direction;
};

void main() {
    Ray ray;
    ray.origin = vec3(0.0, 0.0, 0.0);
    ray.direction = vec3(0.0, 0.0, 1.0);

    fragColor = ubo.backgroundColor;
}
