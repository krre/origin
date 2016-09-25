#include "Camera.h"

Camera::Camera(QObject* parent) : QObject(parent) {
    m_cameraToWorld = glm::translate(m_cameraToWorld, glm::vec3(0.0, 0.0, 5.0));
    m_worldToCamera = glm::inverse(m_cameraToWorld);
}
