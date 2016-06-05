#include "Plane.h"

Plane::Plane() {
    vertexShader.load("Base.vs", GL_VERTEX_SHADER);
    fragmentShader.load("Base.fs", GL_FRAGMENT_SHADER);
    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use(true);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Plane::draw() {
//    print("draw plane");
    glPointSize(200);
    glDrawArrays(GL_POINTS, 0, 1);
}
