#include "Plane.h"

Plane::Plane(int width, int height) : width(width), height(height),
        vertexShader(GL_VERTEX_SHADER),
        fragmentShader(GL_FRAGMENT_SHADER),
        buffer(GL_ARRAY_BUFFER) {
    vertexShader.load("Base.vs");
    fragmentShader.load("Base.fs");

    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use();

    const GLfloat data[] = { -1.0f, -1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f,
                            0.0f,  1.0f, 0.0f, };
    buffer.setData(data, sizeof(data));


}

void Plane::draw() {
//    print("draw plane");
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.getId());
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
}
