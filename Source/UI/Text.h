#pragma once
#include "Control.h"
#include "../Graphics/OpenGL/Program.h"
#include <glm/glm.hpp>

class Text : public Control {

    struct Character {
        GLuint textureId;   // ID handle of the glyph texture
        glm::ivec2 size;    // Size of glyph
        glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
        GLuint advance;    // Horizontal offset to advance to next glyph
    };

public:
    Text();
    void setText(const string& text);
    string getText() const { return text; }

    void setColor(const glm::vec4& color);
    glm::vec4 getColor() const { return color; }

    void setScale(float scale);
    float getScale() const { return scale; }

    void setFontSize(int fontSize);

    void render(float dt) override;

private:
    string text;
    glm::vec4 color;
    float scale = 1.0;
    Program fontProgram;
    std::map<GLchar, Character> characters;
    GLuint vao, vbo;
    int fontSize = 16;
};
