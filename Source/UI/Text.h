#pragma once
#include "Control.h"
#include "../Graphics/OpenGL/Program.h"

class Text : public Control {

public:
    Text();
    void setText(const string& text);
    string getText() const { return text; }
    void render(float dt) override;

private:
    string text;
    Program fontProgram;
};
