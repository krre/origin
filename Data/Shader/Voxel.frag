// Rendering algorithm is based on article:
// Samuli Laine and Tero Karras.
// Efficient Sparse Voxel Octrees – Analysis, Extensions, and Implementation.
// NVIDIA Technical Report NVR-2010-001, 2010.
// https://mediatech.aalto.fi/~samuli/publications/laine2010tr1_paper.pdf
// http://code.google.com/p/efficient-sparse-voxel-octrees
#version 330 core

struct AABB {
    vec3 min;
    vec3 max;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

const AABB aabb = AABB(vec3(-1.0, -1.0, -1.0) , vec3(1.0, 1.0, 1.0));
const int scaleMax = 23;  // Maximum scale (number of float mantissa bits)
const float epsilon = exp2(-scaleMax);

uniform samplerBuffer objects;
uniform usamplerBuffer octrees;

uniform vec3 backgroundColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform float ambientStrength;
uniform int objectCount;
uniform int objectStride;

out vec4 color;

Ray constructRay(in int index) {
    int offset = index * objectStride + 4;
    Ray ray;
    ray.origin = vec3(texelFetch(objects, offset++));
    vec3 startCornerPos = vec3(texelFetch(objects, offset++));
    vec3 stepW = vec3(texelFetch(objects, offset++));
    vec3 stepH = vec3(texelFetch(objects, offset));
    ray.direction = normalize(startCornerPos + stepW * gl_FragCoord.x + stepH * gl_FragCoord.y);
    return ray;
}

bool rayAABBIntersect(in Ray ray, out float tmin, out float tmax) {
    float loX = (aabb.min.x - ray.origin.x) / ray.direction.x;
    float hiX = (aabb.max.x - ray.origin.x) / ray.direction.x;

    tmin = min(loX, hiX);
    tmax = max(loX, hiX);

    float loY = (aabb.min.y - ray.origin.y) / ray.direction.y;
    float hiY = (aabb.max.y - ray.origin.y) / ray.direction.y;

    tmin = max(tmin, min(loY, hiY));
    tmax = min(tmax, max(loY, hiY));

    float loZ = (aabb.min.z - ray.origin.z) / ray.direction.z;
    float hiZ = (aabb.max.z - ray.origin.z) / ray.direction.z;

    tmin = max(tmin, min(loZ, hiZ));
    tmax = min(tmax, max(loZ, hiZ));

    return (tmin <= tmax) && (tmax > 0.0f);
}

bool castRay(in Ray ray, in int index, out vec3 color, out float distance) {
    float tmin, tmax;

    if (rayAABBIntersect(ray, tmin, tmax)) {
        int offset = index * objectStride;
        vec3 ambient = ambientStrength * lightColor;
        vec3 hitPointObject = ray.origin + ray.direction * tmin;
        float fixPrecision = 0.00001; // for fix numbers 0.9999999 to 1.0
        vec4 hitNormalObject = vec4(int(hitPointObject.x + fixPrecision), int(hitPointObject.y + fixPrecision), int(hitPointObject.z + fixPrecision), 0.0);
        mat4 octreeToWorld = mat4(texelFetch(objects, offset++), texelFetch(objects, offset++), texelFetch(objects, offset++), texelFetch(objects, offset));
        vec4 hitNormalWorld = normalize(octreeToWorld * hitNormalObject);
        vec3 lightDir = normalize(lightPos);
        vec3 diffuse = max(dot(vec3(hitNormalWorld), lightDir), 0.0) * lightColor;
        vec3 octreeColor = vec3(texelFetch(objects, index * objectStride + 8));
        color = (ambient + diffuse) * octreeColor;
        distance = tmin * octreeToWorld[0][0]; // tmin * scale
        return true;
    }

    return false;
}

void main() {
    vec4 outColor = vec4(backgroundColor, 1.0);
    float distanceMin = 10000;
    for (int i = 0; i < objectCount; i++) {
        Ray ray = constructRay(i);
        vec3 castColor;
        float distance;
        if (castRay(ray, i, castColor, distance)) {
            if (distance < distanceMin) {
                distanceMin = distance;
                outColor = vec4(castColor, 1.0);
            }
        }
    }

    color = outColor;
}
