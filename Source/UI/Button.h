#pragma once
#include "Rectangle.h"

class Button : public Rectangle {

public:
    Button();

    Nano::Signal<void()> clicked;
};
