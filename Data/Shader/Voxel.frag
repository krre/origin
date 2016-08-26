#version 330 core

uniform mat4 cameraMat;
uniform vec3 cameraPos;

struct Ray {
    vec3 origin;
    vec3 direction;
};

Ray constructRay() {
    Ray ray;
    ray.origin = cameraPos;
    return ray;
}

vec4 castRay(in Ray ray) {
//    if (cameraPos.z > 0) {
    if (gl_FragCoord.x < 250.0) {
        return vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        return vec4(1.0, 1.0, 1.0, 1.0);
    }
}

void main() {
    Ray ray = constructRay();
    gl_FragColor = castRay(ray);
}
