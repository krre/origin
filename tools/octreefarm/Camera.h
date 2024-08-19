#pragma once
#include <QObject>
#include <glm/ext.hpp>

class Camera : public QObject {
    Q_OBJECT
public:
    Camera();

    glm::mat4 projective() const { return m_projective; }
    glm::mat4 view() const { return m_view; }
    glm::vec3 position() const { return m_position; }

    void setTarget(const glm::vec3& target);
    void setPosition(const glm::vec3& position);
    void pan(float dx, float dy);
    void rotate(float yaw, float pitch);
    void zoom(float amount);
    void reset();
    void update();
    void resize(int width, int height);

signals:
    void stateChanged();

private:
    const float m_minDistance = 0.1;
    const float m_maxDistance = 50;
    float m_fov = glm::radians(50.0f);
    float m_aspect;
    glm::vec3 m_up;
    glm::vec3 m_look;
    glm::vec3 m_right;

    glm::mat4 m_projective = glm::mat4(1.0);
    glm::mat4 m_view = glm::mat4(1.0);
    glm::vec3 m_position;
    glm::vec3 m_target;
    float m_distance; // from target to position
    float m_yaw;
    float m_pitch;
};
