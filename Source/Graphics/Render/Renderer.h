#pragma once
#include "Core/Object.h"

namespace Origin {

class RenderPassResource;

class Renderer : public Object {

public:
    Renderer(Object* parent = nullptr);
    ~Renderer();

    virtual void draw() = 0;
    virtual RenderPassResource* getRenderPass() const = 0;

    void setActive(bool active);
    bool getActive() const { return active; }

private:
    bool active = true;
};

} // Origin
