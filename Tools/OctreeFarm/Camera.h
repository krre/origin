#pragma once
#include <QObject>
#include <glm/ext.hpp>

class Camera : public QObject {
    Q_OBJECT

public:
    explicit Camera(QObject* parent = 0);
    glm::mat4 cameraToWorld() const { return m_cameraToWorld; }
    void setCameraToWorld(const glm::mat4 cameraToWorld);
    glm::mat4 worldToCamera() const { return m_worldToCamera; }

    float fov() { return m_fov; }
    glm::vec3 up() { return m_up; }
    glm::vec3 look() { return m_look; }
    glm::vec3 right() { return m_right; }

private:
    float m_fov = glm::radians(50.0f);
    float aspect;
    const float distance = 0.5f; // distance from camera to screen
    const glm::vec3 m_up = glm::vec3(0.0, 1.0, 0.0);
    const glm::vec3 m_look = glm::vec3(0.0, 0.0, -1.0);
    const glm::vec3 m_right = glm::vec3(1.0, 0.0, 0.0);

    glm::mat4 m_cameraToWorld = glm::mat4(1.0);
    glm::mat4 m_worldToCamera = glm::mat4(1.0);
    glm::vec3 m_position;
    glm::quat m_rotation;
    float m_scale = 1.0;
    float m_yaw = 0;
    float m_pitch = 0;
};
