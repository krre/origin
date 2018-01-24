#pragma once
#include <QObject>
#include <glm/ext.hpp>

namespace OctreeFarm {

class Camera : public QObject {
    Q_OBJECT

public:
    explicit Camera(QObject* parent = 0);
    glm::mat4 getCameraToWorld() const { return cameraToWorld; }
    void setCameraToWorld(const glm::mat4& cameraToWorld);
    glm::mat4 getWorldToCamera() const { return worldToCamera; }

    void setTarget(const glm::vec3& target);
    void setPosition(const glm::vec3& position);
    void pan(float dx, float dy);
    void rotate(float yaw, float pitch);
    void zoom(float amount);
    void reset();

    float getFov() { return fov; }
    glm::vec3 getUp() { return up; }
    glm::vec3 getLook() { return look; }
    glm::vec3 getRight() { return right; }

private:
    void update();

    const float minDistance = 0.1;
    const float maxDistance = 50;
    float fov = glm::radians(50.0f);
    float aspect;
//    const float distance = 0.5f; // distance from camera to screen
    const glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 up;
    glm::vec3 look;
    glm::vec3 right;

    glm::mat4 cameraToWorld = glm::mat4(1.0);
    glm::mat4 worldToCamera = glm::mat4(1.0);
    glm::vec3 position;
    glm::vec3 target;
    float distance; // from target to position
    float scale;
    float yaw;
    float pitch;
};

} // OctreeFarm
