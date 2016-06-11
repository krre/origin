#include "Camera.h"
#include <glm/ext.hpp>

Camera::Camera() {
    projection = glm::perspective(fov, aspect, near, far);
}

void Camera::setNear(float near) {
    this->near = near;
}

void Camera::setFar(float far) {
    this->far = far;
}

void Camera::setFov(float fov) {
    this->fov = fov;
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
}
