#pragma once
#include "Graphics/Render/RenderWindow.h"

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    ~OpenGLRenderWindow();
    void render() override;

private:
    void saveScreenshotImpl(const std::string& filePath) override;
};
