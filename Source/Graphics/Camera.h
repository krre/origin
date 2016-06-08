#pragma once
#include "../SceneGraph/Node.h"

class Camera : public Node {

public:
    Camera();
    void setNear(float near) { this->near = near; }
    void setFar(float far) { this->far = far; }
    void setFov(float fov) { this->fov = fov; }
    void setAspect(float aspect) { this->aspect = aspect; }

private:
    float near;
    float far;
    float fov;
    float aspect;
};
