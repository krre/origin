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

struct MetaData {
    vec3 origin;
    vec3 startCorner;
    vec3 stepW;
    vec3 stepH;
    uint blockIndex;
};

layout (std430, binding = 2) buffer Meta {
    MetaData data[];
} meta;

layout (location = 0) out vec4 fragColor;

struct Ray {
    vec3 origin;
    vec3 direction;
};

void main() {
    MetaData metaData = meta.data[0];
    Ray ray;
    ray.origin = metaData.origin;
    ray.direction = normalize(metaData.startCorner + metaData.stepW * gl_FragCoord.x + metaData.stepH * gl_FragCoord.y);

//    fragColor = ubo.backgroundColor;
    fragColor = ubo.backgroundColor + ray.origin[0];
}
