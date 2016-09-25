#pragma once
#include <QObject>
#include <glm/ext.hpp>

class Camera : public QObject {
    Q_OBJECT

public:
    explicit Camera(QObject* parent = 0);
    glm::mat4 cameraToWorld() const { return m_cameraToWorld; }
    glm::mat4 worldToCamera() const { return m_worldToCamera; }

private:
    glm::mat4 m_cameraToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToCamera = glm::mat4(1.0);
    glm::vec3 m_position;
    glm::quat m_rotation;
    float m_scale = 1.0;
    float m_yaw = 0;
    float m_pitch = 0;
};
