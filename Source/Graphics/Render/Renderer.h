#pragma once
#include "Core/Object.h"

namespace Origin {

class RenderPassResource;

class Renderer : public Object {

public:
    Renderer(Object* parent = nullptr);
    ~Renderer();

    virtual void init() = 0;
    virtual void render() = 0;
    virtual RenderPassResource* getRenderPass() const = 0;

private:

};

} // Origin
