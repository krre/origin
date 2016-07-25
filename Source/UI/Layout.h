#pragma once
#include "Rectangle.h"

class Layout : public Rectangle {

public:
    Layout();
    virtual void resize(int width, int height);
};
