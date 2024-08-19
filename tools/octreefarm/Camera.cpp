#include "Camera.h"
#include <QtCore>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {
    reset();
}

void Camera::setTarget(const glm::vec3& target) {
    m_target = target;
    m_distance = glm::distance(m_position, target);
    update();
}

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
    update();
}

void Camera::pan(float dx, float dy) {
    glm::vec3 x = m_right * dx;
    glm::vec3 y = m_up * dy;
    m_position += x + y;
    m_target += x + y;
    update();
}

void Camera::rotate(float yaw, float pitch) {
    m_yaw = yaw;
    m_pitch = pitch;
    update();
}

void Camera::zoom(float amount) {
    m_position += m_look * amount;
    update();
}

void Camera::reset() {
    m_position = glm::vec3(0.0, 0.0, 3.0);
    setTarget(glm::vec3(0.0, 0.0, 0.0));
    m_yaw = 0;
    m_pitch = 0;
    m_up = glm::vec3(0.0, 1.0, 0.0);
    m_look = glm::vec3(0.0, 0.0, -1.0);
    m_right = glm::vec3(1.0, 0.0, 0.0);
    update();
}

void Camera::update() {
    m_distance = glm::distance(m_position, m_target);
    m_distance = std::max(m_minDistance, std::min(m_distance, m_maxDistance));

    glm::mat4 R = glm::yawPitchRoll(glm::radians(m_yaw), glm::radians(m_pitch), 0.0f);
    glm::vec3 T = glm::vec3(0, 0, m_distance);
    T = glm::vec3(R * glm::vec4(T, 0.0f));
    m_position = m_target + T;
    m_look = glm::normalize(m_target - m_position);
    m_up = glm::vec3(R * glm::vec4(glm::vec3(0.0, 1.0, 0.0), 0.0f));
    m_right = glm::cross(m_look, m_up);
    m_view = glm::lookAt(m_position, m_target, m_up);
    emit stateChanged();
}

void Camera::resize(int width, int height) {
    if (!(width || height)) return;

    float aspect = (float)width / height;
    m_projective = glm::perspective(m_fov, aspect, 0.1f, 100.0f);
    update();
}
