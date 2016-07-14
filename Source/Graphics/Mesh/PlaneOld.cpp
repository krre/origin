#include "PlaneOld.h"
#include "../Core/App.h"
#include "../Resource/ResourceManager.h"
#include <glm/ext.hpp>

PlaneOld::PlaneOld(int width, int height) : width(width), height(height),
        vbo(GL_ARRAY_BUFFER),
        colorBuffer(GL_ARRAY_BUFFER) {

    baseShaderGroup = ResourceManager::getInstance()->getShaderGroup("BaseShaderGroup");
    matrix = glGetUniformLocation(baseShaderGroup->getProgram(), "mvp");

    vao.bind();

    // Vertex buffer
    vbo.bind();
    static const GLfloat vertexData[] = {
        -1.0f * width, 0.0f, -1.0f * height,
        1.0f * width, 0.0f, 1.0f * height,
        1.0f * width, 0.0f, -1.0f * height,

        -1.0f * width,  0.0f, -1.0f * height,
        -1.0f * width,  0.0f, 1.0f * height,
        1.0f * width,  0.0f, 1.0f * height,
    };
    vbo.setData(vertexData, sizeof(vertexData));

    static const GLfloat colorData[] = {
        0.000f,  1.000f,  0.000f,
        0.000f,  0.000f,  1.000f,
        0.000f,  1.000f,  1.000f,
        1.000f,  1.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  1.000f
    };

    glVertexAttribPointer(
       0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    // Color buffer
    colorBuffer.bind();
    colorBuffer.setData(colorData, sizeof(colorData));

    glVertexAttribPointer(
       1,                  // attribute. No particular reason for 1, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);

    vao.unbind();
}

void PlaneOld::draw() {
    baseShaderGroup->use();
    glm::mat4 projection = App::getInstance()->getViewport()->getCamera()->getProjection();
    glm::mat4 view = App::getInstance()->getViewport()->getCamera()->getView();
    mvp = projection * view * getModelMatrix();
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
//    glm::vec4 pos = mvp * glm::vec4(-1.0f, 0.0f, -1.0f, 1.0f);
//    print(glm::to_std::string(pos));

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    vao.unbind();
}
