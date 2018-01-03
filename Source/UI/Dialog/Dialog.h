#pragma once
#include "Scene/Scene2D.h"

namespace Origin {

class Dialog : public Scene2D {

public:
    Dialog();
    void close();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
};

} // Origin
