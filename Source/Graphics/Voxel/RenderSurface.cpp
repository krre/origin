#include "RenderSurface.h"
#include "../Event/Event.h"
#include "../Resource/ResourceManager.h"

RenderSurface::RenderSurface() :
    texture(GL_TEXTURE_2D),
    VBO(GL_ARRAY_BUFFER) {
    surfaceShaderGroup = ResourceManager::getInstance()->getShaderGroup("SurfaceShaderGroup");

    GLfloat vertices[] = {
        // Positions          // Texture Coords
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f, // Top Left
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // Top Right

        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // Bottom Left
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f  // Top Right
    };

    VAO.bind();

    VBO.bind();
    VBO.setData(vertices, sizeof(vertices));

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    VAO.unbind();


    Event::getInstance()->windowResize.connect<RenderSurface, &RenderSurface::onWindowResize>(this);
}

RenderSurface::~RenderSurface() {
    delete data;
    delete depth;
}

void RenderSurface::draw(float dt) {
    texture.bind();
    glTexImage2D(texture.getType(), 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    surfaceShaderGroup->use();
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO.unbind();
}

void RenderSurface::clear() {
    uint32_t color = 0xff0000ffu;
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

    data = new uint32_t[width * height];
    depth = new uint32_t[width * height];
    clear();
}
