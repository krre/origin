#pragma once
#include "../Scene/Node.h"
#include <glm/glm.hpp>

class Camera : public Node {

public:
    Camera();
    void setNear(float near);
    void setFar(float far);
    void setFov(float fov);
    void setAspect(float aspect);
    const glm::mat4& getProjection() const { return projection; }
    const glm::mat4& getView() { glm::inverse(getModelMatrix()); }

private:
    float near = 0.1f;
    float far = 100.0f;
    float fov = glm::radians(50.0f);
    float aspect = 800.0f / 480.0f;
    glm::mat4 projection;

    void windowResize(int width, int height);
};
