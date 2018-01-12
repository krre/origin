#pragma once
#include "Graphics/Render/Renderer.h"

namespace Origin {

class OpenGLRenderer : public Renderer {

public:
    OpenGLRenderer();

private:
    void renderQueue() override;
};

} // Origin
