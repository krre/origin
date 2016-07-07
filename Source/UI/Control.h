#pragma once
#include "../Core/Object.h"
#include <glm/glm.hpp>

class Control : public Object {

public:
    Control();
    void setPosition(const glm::vec2& position);
    glm::vec2 getPostion() const { return position; }
    void render(float dt);

private:
    glm::vec2 position;
};
