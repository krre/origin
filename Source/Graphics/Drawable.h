#pragma once
#include "../Core/Object.h"

class Drawable : Object {

public:
    Drawable();
    virtual void draw(float dt) = 0;
    virtual void update(float dt) {}

    virtual void setVisible(bool visible);
    bool getVisible() const { return visible; }

    float getOpacity() const { return opacity; }
    void setOpacity(float opacity);

protected:
    bool visible = true;
    float opacity = 1.0;
};
