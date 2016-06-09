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

private:
    float near;
    float far;
    float fov;
    float aspect;
    glm::mat4 projection;
};
