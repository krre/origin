#pragma once
#include "../Graphics/Drawable.h"
#include <glm/glm.hpp>

class Control : public Origin::Drawable {

public:
    Control(int width = 0, int height = 0);
    void setPosition(const glm::vec2& position);
    glm::vec2 getPosition() const { return position; }

    glm::vec2 getSize() const { return size; }
    void setSize(int width, int height);

    void setScale(float scale);
    float getScale() const { return scale; }

    void resize(int width, int height);

    float getZ() const { return z; }
    void setZ(float z);

protected:
    glm::vec2 position;
    glm::vec2 size;
    float scale = 1.0;
    float z = 0.0f;
};
