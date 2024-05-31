#include "Camera.h"
#include <QtCore>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {
    reset();
}

void Camera::setTarget(const glm::vec3& target) {
    this->target = target;
    distance = glm::distance(m_position, target);
    update();
}

void Camera::setPosition(const glm::vec3& position) {
    this->m_position = position;
    update();
}

void Camera::pan(float dx, float dy) {
    glm::vec3 x = right * dx;
    glm::vec3 y = up * dy;
    m_position += x + y;
    target += x + y;
    update();
}

void Camera::rotate(float yaw, float pitch) {
    this->yaw = yaw;
    this->pitch = pitch;
    update();
}

void Camera::zoom(float amount) {
    m_position += look * amount;
    update();
}

void Camera::reset() {
    m_position = glm::vec3(0.0, 0.0, 3.0);
    setTarget(glm::vec3(0.0, 0.0, 0.0));
    yaw = 0;
    pitch = 0;
    up = glm::vec3(0.0, 1.0, 0.0);
    look = glm::vec3(0.0, 0.0, -1.0);
    right = glm::vec3(1.0, 0.0, 0.0);
    update();
}

void Camera::update() {
    distance = glm::distance(m_position, target);
    distance = std::max(minDistance, std::min(distance, maxDistance));

    glm::mat4 R = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);
    glm::vec3 T = glm::vec3(0, 0, distance);
    T = glm::vec3(R * glm::vec4(T, 0.0f));
    m_position = target + T;
    look = glm::normalize(target - m_position);
    up = glm::vec3(R * glm::vec4(UP, 0.0f));
    right = glm::cross(look, up);
    m_view = glm::lookAt(m_position, target, up);
    emit stateChanged();
}

void Camera::resize(int width, int height) {
    if (!(width || height)) return;

    float aspect = (float)width / height;
    m_projective = glm::perspective(fov, aspect, 0.1f, 100.0f);
    update();
}
