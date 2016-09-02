#version 330 core
#extension GL_ARB_shader_storage_buffer_object : require

struct AABB {
    vec3 min;
    vec3 max;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

out vec4 color;

uniform mat4 octreeToWorld;
uniform mat4 cameraToWorld;

uniform vec3 backgroundColor;
uniform vec3 octreeColor;
uniform vec3 lightColor;

uniform vec3 cameraPos;
uniform vec3 lightPos;

uniform vec3 startCornerPos;
uniform vec3 stepW;
uniform vec3 stepH;

uniform AABB aabb;
uniform float ambientStrength;

layout (std430, binding = 0) buffer OctreeBuffer {
    int count;
};

Ray constructRay() {
    Ray ray;
    ray.origin = cameraPos;
    ray.direction = normalize(startCornerPos + stepW * gl_FragCoord.x + stepH * gl_FragCoord.y);
    return ray;
}

bool rayAABBIntersect(in Ray ray, out float t) {
    float loX = (aabb.min.x - ray.origin.x) / ray.direction.x;
    float hiX = (aabb.max.x - ray.origin.x) / ray.direction.x;

    float tmin = min(loX, hiX);
    float tmax = max(loX, hiX);

    float loY = (aabb.min.y - ray.origin.y) / ray.direction.y;
    float hiY = (aabb.max.y - ray.origin.y) / ray.direction.y;

    tmin = max(tmin, min(loY, hiY));
    tmax = min(tmax, max(loY, hiY));

    float loZ = (aabb.min.z - ray.origin.z) / ray.direction.z;
    float hiZ = (aabb.max.z - ray.origin.z) / ray.direction.z;

    tmin = max(tmin, min(loZ, hiZ));
    tmax = min(tmax, max(loZ, hiZ));
    t = tmin;

    return (tmin <= tmax) && (tmax > 0.0f);
}

vec4 castRay(in Ray ray) {
    float t;

    vec3 ambient = ambientStrength * lightColor;

    if (rayAABBIntersect(ray, t)) {
        vec3 hitPointObject = ray.origin + ray.direction * t;
        float fixPrecision = 0.00001; // for fix numbers 0.9999999 to 1.0
        vec4 hitNormalObject = vec4(int(hitPointObject.x + fixPrecision), int(hitPointObject.y + fixPrecision), int(hitPointObject.z + fixPrecision), 0.0);
        vec4 hitNormalWorld = normalize(octreeToWorld * hitNormalObject);
        vec3 lightDir = normalize(lightPos);
        vec3 diffuse = max(dot(vec3(hitNormalWorld), lightDir), 0.0) * lightColor;
        vec3 color = (ambient + diffuse) * octreeColor;
        return vec4(color, 1.0);
    } else {
        return vec4(backgroundColor, 1.0);
    }
}

void main() {
    Ray ray = constructRay();
    color = castRay(ray);
}
