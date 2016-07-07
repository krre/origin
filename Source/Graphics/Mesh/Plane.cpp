#include "Plane.h"
#include "../Core/App.h"
#include <glm/ext.hpp>

Plane::Plane(int width, int height) : width(width), height(height),
        vertexShader(GL_VERTEX_SHADER),
        fragmentShader(GL_FRAGMENT_SHADER),
        vbo(GL_ARRAY_BUFFER),
        colorBuffer(GL_ARRAY_BUFFER) {
    vertexShader.load("Base.vert");
    fragmentShader.load("Base.frag");

    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();

    static const GLfloat vertexData[] = {
        -1.0f * width, 0.0f, -1.0f * height,
        1.0f * width, 0.0f, 1.0f * height,
        1.0f * width, 0.0f, -1.0f * height,

        -1.0f * width,  0.0f, -1.0f * height,
        -1.0f * width,  0.0f, 1.0f * height,
        1.0f * width,  0.0f, 1.0f * height,
    };
    vbo.bind();
    vbo.setData(vertexData, sizeof(vertexData));

    matrix = glGetUniformLocation(programShader.getId(), "mvp");

    static const GLfloat colorData[] = {
        0.000f,  1.000f,  0.000f,
        0.000f,  0.000f,  1.000f,
        0.000f,  1.000f,  1.000f,
        1.000f,  1.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  1.000f
    };

    colorBuffer.bind();
    colorBuffer.setData(colorData, sizeof(colorData));
}

void Plane::draw() {
    programShader.use();
    glm::mat4 projection = App::getInstance()->getViewport()->getCamera()->getProjection();
    glm::mat4 view = App::getInstance()->getViewport()->getCamera()->getView();
    mvp = projection * view * getModelMatrix();

//    vec4 pos = mvp * vec4(-1.0f, 0.0f, -1.0f, 1.0f);
//    print(glm::to_string(pos));

    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    vbo.bind();
    glVertexAttribPointer(
       0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    colorBuffer.bind();
    glVertexAttribPointer(
       1,                  // attribute. No particular reason for 1, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
