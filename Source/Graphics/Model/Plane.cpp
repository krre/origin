#include "Plane.h"

Plane::Plane(int width, int height) : width(width), height(height),
        vertexShader(GL_VERTEX_SHADER),
        fragmentShader(GL_FRAGMENT_SHADER),
        vertexBuffer(GL_ARRAY_BUFFER),
        colorBuffer(GL_ARRAY_BUFFER) {
    vertexShader.load("Base.vs");
    fragmentShader.load("Base.fs");

    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use();

    static const GLfloat vertexData[] = {
        -1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,

        -1.0f,  0.0f, -1.0f,
        -1.0f,  0.0f, 1.0f,
        1.0f,  0.0f, 1.0f,
    };
    vertexBuffer.bind();
    vertexBuffer.setData(vertexData, sizeof(vertexData));

    matrix = glGetUniformLocation(programShader.getId(), "mvp");
    glm::mat4 projection = glm::perspective(glm::radians(50.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 2, 2), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    mvp = projection * view * modelMatrix;

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
//    print("draw plane");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    vertexBuffer.bind();
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
