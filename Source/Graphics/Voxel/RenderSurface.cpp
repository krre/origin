#include "RenderSurface.h"
#include "../Event/Event.h"
#include "../Resource/ResourceManager.h"
#include "../Core/App.h"

RenderSurface::RenderSurface() :
    texture(GL_TEXTURE_RECTANGLE),
    VBO(GL_ARRAY_BUFFER) {

    surfaceShaderGroup = ResourceManager::getInstance()->getShaderGroup("SurfaceShaderGroup");
    voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");

    GLfloat vertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f,

        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };

    VAO.bind();

    VBO.bind();
    VBO.setData(vertices, sizeof(vertices));

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VAO.unbind();

    Event::getInstance()->windowResize.connect<RenderSurface, &RenderSurface::onWindowResize>(this);
}

RenderSurface::~RenderSurface() {
    delete data;
    delete depth;
}

void RenderSurface::draw(float dt) {
    octreeRenderer.render(this);

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO.unbind();
}

void RenderSurface::clear() {
    uint32 color = 0xc4d3d3ffu;
    std::fill_n(data, width * height, color);
    std::fill_n(depth, width * height, ~0u);
}

void RenderSurface::onWindowResize(int width, int height) {
    this->width = width;
    this->height = height;

    if (data != nullptr) {
        delete data;
    }

    if (depth != nullptr) {
        delete depth;
    }

    data = new uint32[width * height];
    depth = new uint32[width * height];
    clear();
}
