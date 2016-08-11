#pragma once
#include "../Drawable.h"
#include "../Graphics/ShaderGroup.h"
#include "../Graphics/OpenGL/Texture.h"
#include "../Graphics/OpenGL/VertexArray.h"
#include "../Graphics/OpenGL/Buffer.h"

class RenderSurface : public Drawable {

public:
    RenderSurface();
    ~RenderSurface();
    void draw(float dt) override;
    void clear();
    void update(float dt) override;

private:
    void onWindowResize(int width, int height);
    uint32_t* data = nullptr;
    uint32_t* depth = nullptr;
    ShaderGroup* surfaceShaderGroup;

    Texture texture;
    VertexArray VAO;
    Buffer VBO;

    int width = 0;
    int height = 0;
};
