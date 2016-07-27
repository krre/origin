#pragma once
#include "Control.h"

class Button : public Control {

public:
    Button();

    Nano::Signal<void()> clicked;
};
