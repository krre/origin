// Rendering algorithm is based on article:
// Samuli Laine and Tero Karras.
// Efficient Sparse Voxel Octrees – Analysis, Extensions, and Implementation.
// NVIDIA Technical Report NVR-2010-001, 2010.
// https://mediatech.aalto.fi/~samuli/publications/laine2010tr1_paper.pdf
// http://code.google.com/p/efficient-sparse-voxel-octrees
#version 330 core

#if 1
#extension GL_ARB_shader_storage_buffer_object : require
layout (std430, binding = 0) buffer OctreeBuffer {
    int count;
};
#endif

struct AABB {
    vec3 min;
    vec3 max;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

const AABB aabb = AABB(vec3(-1.0, -1.0, -1.0) , vec3(1.0, 1.0, 1.0));
const int s_max = 23;  // Maximum scale (number of float mantissa bits)
const float epsilon = exp2(-s_max);

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
        // NEW VERSION
        ivec2 stack[s_max + 1]; // Stack of parent voxels

        // Get rid of small ray direction components to avoid division by zero
        float dx = (abs(ray.direction.x) < epsilon ? epsilon * sign(ray.direction.x) : ray.direction.x);
        float dy = (abs(ray.direction.y) < epsilon ? epsilon * sign(ray.direction.y) : ray.direction.y);
        float dz = (abs(ray.direction.z) < epsilon ? epsilon * sign(ray.direction.z) : ray.direction.z);

        // Precompute the coefficients of tx(x), ty(y), and tz(z).
        // The octree is assumed to reside at coordinates [1, 2]
        float tx_coef = 1.0f / -abs(dx);
        float ty_coef = 1.0f / -abs(dy);
        float tz_coef = 1.0f / -abs(dz);

        float tx_bias = tx_coef * ray.origin.x;
        float ty_bias = ty_coef * ray.origin.y;
        float tz_bias = tz_coef * ray.origin.z;

        // Select octant mask to mirror the coordinate system so
        // that ray direction is negative along each axis
        int octant_mask = 7;
        if (dx > 0.0f) octant_mask ^= 1, tx_bias = 3.0f * tx_coef - tx_bias;
        if (dy > 0.0f) octant_mask ^= 2, ty_bias = 3.0f * ty_coef - ty_bias;
        if (dz > 0.0f) octant_mask ^= 4, tz_bias = 3.0f * tz_coef - tz_bias;

        // Initialize the active span of t-values
        float t_min = max(max(2.0f * tx_coef - tx_bias, 2.0f * ty_coef - ty_bias), 2.0f * tz_coef - tz_bias);
        float t_max = min(min(tx_coef - tx_bias, ty_coef - ty_bias), tz_coef - tz_bias);
        float h = t_max;
        t_min = max(t_min, 0.0f);
        t_max = min(t_max, 1.0f);


        // OLD VERSION
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
