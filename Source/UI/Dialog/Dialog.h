#pragma once
#include "UI/Rectangle.h"

namespace Origin {

class Dialog : public Rectangle {

public:
    Dialog();
    void close();
    void resizeToContent();
    void setPadding(int padding);

private:
    void keyPressed(const SDL_KeyboardEvent& event) override;
    int padding = 7;
};

} // Origin
