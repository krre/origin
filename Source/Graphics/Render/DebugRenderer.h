#pragma once
#include "Renderer.h"

namespace Origin {

class DebugRenderer : public Renderer {

public:
    DebugRenderer(Object* parent = nullptr);
    ~DebugRenderer();

    static DebugRenderer* get();

    void draw() override;
    RenderLayer* getRenderLayer() const override;

private:

};

} // Origin
