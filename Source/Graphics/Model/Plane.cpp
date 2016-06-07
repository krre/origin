#include "Plane.h"

Plane::Plane(int width, int height) : width(width), height(height),
        vertexShader(GL_VERTEX_SHADER), fragmentShader(GL_FRAGMENT_SHADER) {
    vertexShader.load("Base.vs");
    fragmentShader.load("Base.fs");

    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use();
}

void Plane::draw() {
//    print("draw plane");
    glPointSize(200);
    glDrawArrays(GL_POINTS, 0, 1);
}
