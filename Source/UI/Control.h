#pragma once
#include "../Graphics/Drawable.h"
#include <glm/glm.hpp>

class Control : public Drawable {

public:
    Control();
    void setPosition(const glm::vec2& position);
    glm::vec2 getPosition() const { return position; }

    int getWidth() const { return width; }
    void setWidth(int width);

    int getHeight() const { return heght; }
    void setHeight(int height);

    void resize(int width, int height);

protected:
    glm::vec2 position;
    int width = 0;
    int heght = 0;
};
