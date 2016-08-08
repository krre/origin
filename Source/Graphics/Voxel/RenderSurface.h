#pragma once
#include "../Drawable.h"
#include "../Graphics/ShaderGroup.h"
#include "../Graphics/OpenGL/Texture.h"

class RenderSurface : public Drawable {

public:
    RenderSurface();
    ~RenderSurface();
    void draw(float dt) override;

private:
    void onWindowResize(int width, int height);
    uint32_t* data = nullptr;
    uint32_t* depth = nullptr;
    ShaderGroup* surfaceShaderGroup;
    Texture texture;
    int width = 0;
    int height = 0;
};
