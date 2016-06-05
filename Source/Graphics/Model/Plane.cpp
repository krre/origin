#include "Plane.h"

Plane::Plane() {
    vertexShader.load("Base.vs", GL_VERTEX_SHADER);
    fragmentShader.load("Base.fs", GL_FRAGMENT_SHADER);
    programShader.addShader(vertexShader);
    programShader.addShader(fragmentShader);
    programShader.link();
    programShader.use(true);
}

void Plane::draw() {
//    print("draw plane");
}
