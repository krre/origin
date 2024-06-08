#pragma once
#include "ui/Rectangle.h"

class Dialog : public Rectangle {
public:
    Dialog();
    void close();
    void resizeToContent();
    void setPadding(int padding);

private:
    void keyPressed(const SDL_KeyboardEvent& event) override;
    int m_padding = 7;
};
