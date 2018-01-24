#include "Camera.h"
#include <QtCore>
#include <iostream>

namespace OctreeFarm {

Camera::Camera(QObject* parent) : QObject(parent) {
    reset();
}

void Camera::setCameraToWorld(const glm::mat4& cameraToWorld) {
    this->cameraToWorld = cameraToWorld;
    worldToCamera = glm::inverse(cameraToWorld);
}

void Camera::setTarget(const glm::vec3& target) {
    this->target = target;
    distance = glm::distance(position, target);
}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
    setCameraToWorld(glm::translate(cameraToWorld, position));
}

void Camera::pan(float dx, float dy) {
    glm::vec3 x = right * dx;
    glm::vec3 y = up * dy;
    position += x + y;
    target += x + y;
    update();
}

void Camera::rotate(float yaw, float pitch) {
    this->yaw = yaw;
    this->pitch = pitch;
    update();
}

void Camera::zoom(float amount) {
    position += look * amount;
    distance = glm::distance(position, target);
    distance = std::max(minDistance, std::min(distance, maxDistance));
    update();
}

void Camera::reset() {
    position = glm::vec3(0.0, 0.0, 3.0);
    setTarget(glm::vec3(0.0, 0.0, 0.0));
    scale = 1.0;
    yaw = 0;
    pitch = 0;
    up = glm::vec3(0.0, 1.0, 0.0);
    look = glm::vec3(0.0, 0.0, -1.0);
    right = glm::vec3(1.0, 0.0, 0.0);
    update();
}

void Camera::update() {
    glm::mat4 R = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);
    glm::vec3 T = glm::vec3(0, 0, distance);
    T = glm::vec3(R * glm::vec4(T, 0.0f));
    position = target + T;
    look = glm::normalize(target - position);
    up = glm::vec3(R * glm::vec4(UP, 0.0f));
    right = glm::cross(look, up);
    worldToCamera = glm::lookAt(position, target, up);
    cameraToWorld = glm::inverse(worldToCamera);
}

} // OctreeFarm
