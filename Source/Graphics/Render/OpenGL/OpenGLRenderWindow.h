#pragma once
#include "Graphics/Render/RenderWindow.h"

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    void swapBuffers() override;
};
