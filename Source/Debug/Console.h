#pragma once
#include "UI/TextEdit.h"

struct SDL_KeyboardEvent;
class Label;

class Console : public TextEdit {

public:
    Console(Control* parent = nullptr);
    void reset();

private:
    void keyPressed(const SDL_KeyboardEvent& event) override;
    void execute();
};
