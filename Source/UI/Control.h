#pragma once
#include "../Graphics/Drawable.h"
#include <glm/glm.hpp>

class Control : public Drawable {

public:
    Control();
    void setPosition(const glm::vec2& position);
    glm::vec2 getPostion() const { return position; }

protected:
    glm::vec2 position;
};
