#pragma once
#include "Graphics/Render/RenderWindow.h"

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    ~OpenGLRenderWindow();
    void render() override;

private:
    void onResize(int width, int height) override;
    void saveScreenshotImpl(const std::string& filePath) override;
    Uint32 getSurfaceFlag() const override;
};
