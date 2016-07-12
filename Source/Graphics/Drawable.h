#pragma once
#include "../Core/Object.h"

class Drawable : Object {

public:
    Drawable();
    virtual void draw(float dt) = 0;

    void setVisible(bool visible);
    bool getVisible() const { return visible; }

private:
    bool visible = true;
};
