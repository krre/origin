#pragma once
#include "Graphics/Render/RenderWindow.h"
#include <SDL_video.h>

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;

private:
    SDL_GLContext context;
};
