#pragma once
#include "Control.h"
#include "../Graphics/OpenGL/Program.h"
#include <glm/glm.hpp>

class Text : public Control {

public:
    Text();
    void setText(const string& text);
    string getText() const { return text; }

    void setColor(const glm::vec4& color);
    glm::vec4 getColor() const { return color; }
    void render(float dt) override;

private:
    string text;
    glm::vec4 color;
    Program fontProgram;
};
