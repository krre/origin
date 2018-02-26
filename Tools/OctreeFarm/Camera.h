#pragma once
#include <QObject>
#include <glm/ext.hpp>

namespace OctreeFarm {

class Camera : public QObject {
    Q_OBJECT

public:
    explicit Camera(QObject* parent = 0);

    glm::mat4 getProjective() const { return projective; }
    glm::mat4 getView() const { return view; }

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

    glm::mat4 projective = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);
    glm::vec3 position;
    glm::vec3 target;
    float distance; // from target to position
    float yaw;
    float pitch;
};

} // OctreeFarm
