#pragma once
#include "../Core/Object.h"

class Drawable : Object {

public:
    Drawable();
    virtual void draw(float dt) = 0;

    virtual void setVisible(bool visible);
    bool getVisible() const { return visible; }

protected:
    bool visible = true;
};
