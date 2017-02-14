#pragma once
#include "../Graphics/Drawable.h"
#include <glm/glm.hpp>

class Control : public Origin::Drawable {

public:
    Control(int width = 0, int height = 0);
    void setPosition(const glm::vec2& position);
    glm::vec2 getPosition() const { return position; }

    int getWidth() const { return width; }
    void setWidth(int width);

    int getHeight() const { return height; }
    void setHeight(int height);

    void setScale(float scale);
    float getScale() const { return scale; }

    void resize(int width, int height);

    float getZ() const { return z; }
    void setZ(float z);

protected:
    glm::vec2 position;
    int width;
    int height;
    float scale = 1.0;
    float z = 0.0f;
};
