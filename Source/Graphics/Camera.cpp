#include "Camera.h"
#include "../Event/Event.h"
#include <glm/ext.hpp>

Camera::Camera() {
    projection = glm::perspective(fov, aspect, near, far);
    Event::getInstance()->windowResize.connect<Camera, &Camera::windowResize>(this);
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

void Camera::windowResize(int width, int height) {
    aspect = width * 1.0f / height;
    projection = glm::perspective(fov, aspect, near, far);
}
