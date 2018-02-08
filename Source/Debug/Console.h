#pragma once
#include "UI/TextEdit.h"
#include <SDL.h>
#include <memory>

namespace Origin {

class Label;

class Console : public TextEdit {

public:
    Console(Control* parent = nullptr);

private:
    void execute();
    Label* cmdLine;
};

} // Origin
