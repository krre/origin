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
    const float minDistance = 0.1;
    const float maxDistance = 50;
    float fov = glm::radians(50.0f);
    float aspect;
    const glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 up;
    glm::vec3 look;
    glm::vec3 right;

    glm::mat4 m_projective = glm::mat4(1.0);
    glm::mat4 m_view = glm::mat4(1.0);
    glm::vec3 m_position;
    glm::vec3 target;
    float distance; // from target to position
    float yaw;
    float pitch;
};
