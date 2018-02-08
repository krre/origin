#pragma once
#include "UI/Control.h"
#include <SDL.h>
#include <memory>

namespace Origin {

class Label;

class Console : public Control {

public:
    Console(Control* parent = nullptr);

private:
    void execute();
    Label* cmdLine;
};

} // Origin
