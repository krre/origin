#pragma once
#include "../Drawable.h"
#include "../Graphics/OpenGL/ShaderGroup.h"
#include "../Graphics/OpenGL/Texture.h"
#include "../Graphics/OpenGL/VertexArray.h"
#include "../Graphics/OpenGL/Buffer.h"
#include "../Graphics/Voxel/OctreeRenderer.h"

//class OctreeRenderer;

class RenderSurface : public Drawable {

public:
    RenderSurface();
    ~RenderSurface();
    void draw(float dt) override;
    void clear();
    void update(float dt) override;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    uint32* getData() const { return data; }

private:
    void onWindowResize(int width, int height);

    OctreeRenderer octreeRenderer;
    uint32* data = nullptr;
    uint32* depth = nullptr;
    int width = 0;
    int height = 0;

    ShaderGroup* surfaceShaderGroup;
    ShaderGroup* voxelShaderGroup;
    Texture texture;
    VertexArray VAO;
    Buffer VBO;

    bool voxel = false; // temporary while test voxel shader
};
