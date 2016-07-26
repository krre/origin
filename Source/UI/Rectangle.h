#pragma once
#include "Control.h"
#include <glm/glm.hpp>

class Rectangle : public Control {

public:
    Rectangle();
    void draw(float dt) override;

    glm::vec3 getColor() const { return color; }
    void setColor(const glm::vec3& color);

protected:
    glm::vec3 color;
};
