#pragma once
#include "UI/Rectangle.h"

namespace Origin {

class Dialog : public Rectangle {

public:
    Dialog();
    void close();
    void resizeToContent();

private:
    void keyPressed(const SDL_KeyboardEvent& event) override;
};

} // Origin
