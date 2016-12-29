#pragma once
#include "../Core/Object.h"

// Use namespace to prevent conflict with Drawable in X11
namespace CovenantLand {

class Drawable : Object {

public:
    Drawable();
    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;

    virtual void setVisible(bool visible);
    bool getVisible() const { return visible; }

    float getOpacity() const { return opacity; }
    void setOpacity(float opacity);

protected:
    bool visible = true;
    float opacity = 1.0;
};

} // CovenantLand
