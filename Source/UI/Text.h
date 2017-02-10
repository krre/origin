#pragma once
#include "Control.h"
#include "Font.h"

class Text : public Control {

public:
    Text();
    void setText(const std::string& text);
    std::string getText() const { return text; }

    void setFont(Font* font);
    Font* getFont() const { return font; }

    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const { return color; }

    void setScale(float scale);
    float getScale() const { return scale; }

    void setFontSize(int fontSize);

    void draw(float dt) override;
    void update(float dt) override;

private:
    std::string text;
    Font* font;
    glm::vec3 color;
    float scale = 1.0;
};
