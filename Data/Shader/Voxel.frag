#version 330 core

struct AABB {
    vec3 min;
    vec3 max;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

out vec4 color;

uniform vec3 backgroundColor;
uniform vec3 octreeColor;
uniform vec3 lightColor;

uniform mat4 cameraMat;
uniform vec3 cameraPos;

uniform vec3 w0;
uniform vec3 h0;

uniform vec3 stepW;
uniform vec3 stepH;

uniform vec3 aabbMin;
uniform vec3 aabbMax;

uniform AABB aabb;

Ray constructRay() {
    Ray ray;
    ray.origin = cameraPos;
    ray.direction = normalize(w0 + stepW * gl_FragCoord.x + h0 + stepH * gl_FragCoord.y);
    return ray;
}

bool rayAABBIntersect(in Ray ray, in AABB aabb) {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    vec3 bounds[2];
//    bounds[0] = aabb.min;
//    bounds[1] = aabb.max;
    bounds[0] = aabbMin;
    bounds[1] = aabbMax;

    ivec3 sign;

    sign.x = int(ray.direction.x < 0);
    sign.y = int(ray.direction.y < 0);
    sign.z = int(ray.direction.z < 0);

    tmin = (bounds[sign.x].x - ray.origin.x) / ray.direction.x;
    tmax = (bounds[1 - sign.x].x - ray.origin.x) / ray.direction.x;
    tymin = (bounds[sign.y].y - ray.origin.y) / ray.direction.y;
    tymax = (bounds[1 - sign.y].y - ray.origin.y) / ray.direction.y;

    if ((tmin > tymax) || (tymin > tmax)) {
        return false;
    }

    if (tymin > tmin) {
        tmin = tymin;
    }

    if (tymax < tmax) {
        tmax = tymax;
    }

    tzmin = (bounds[sign.z].z - ray.origin.z) / ray.direction.z;
    tzmax = (bounds[1 - sign.z].z - ray.origin.z) / ray.direction.z;

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false;
    }

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    return true;
}

vec4 castRay(in Ray ray) {
    if (rayAABBIntersect(ray, aabb)) {
        return vec4(octreeColor, 1.0);
    } else {
        return vec4(backgroundColor, 1.0);
    }
}

void main() {
    Ray ray = constructRay();
    color = castRay(ray);
}
