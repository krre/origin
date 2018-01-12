#pragma once
#include "Graphics/Render/RenderWindow.h"

namespace Origin {

class OpenGLRenderWindow : public RenderWindow {

public:
    OpenGLRenderWindow();
    ~OpenGLRenderWindow();

private:
    void preRender() override;
    void postRender() override;
    void onResize(int width, int height) override;
    void saveScreenshotImpl(const std::string& filePath) override;
    Uint32 getSurfaceFlag() const override;
    void initImpl() override;
};

} // Origin
