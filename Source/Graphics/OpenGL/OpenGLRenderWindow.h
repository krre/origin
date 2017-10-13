#pragma once
#include "Graphics/Render/RenderWindow.h"
#include <SDL_video.h>

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    void clear() override;
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;

private:
    void setColorBackend(const Color& color) override;

    SDL_GLContext context;
};
