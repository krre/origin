#pragma once
#include "Control.h"
#include "../Graphics/Plane.h"
#include "../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

class Rectangle : public Control {

public:
    Rectangle(int width, int height);
    void draw(float dt) override;

    glm::vec3 getColor() const { return color; }
    void setColor(const glm::vec3& color);

protected:
    glm::vec3 color;
    Plane plane;
    ShaderGroup* baseShaderGroup;
};
