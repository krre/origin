#pragma once
#include "../../SceneGraph/Node.h"
#include "../OpenGL/Shader.h"

class Plane : public Node {

public:
    Plane();
    void draw() override;
private:
    Shader vertexShader;
    Shader fragmentShader;
};
