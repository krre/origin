#pragma once
#include "../../Scene/Scene2D.h"

class Dialog : public Scene2D {

public:
    Dialog();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
};