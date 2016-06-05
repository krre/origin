#include "Plane.h"

Plane::Plane() {
    vertexShader.load("Base.vs", GL_VERTEX_SHADER);
    fragmentShader.load("Base.fs", GL_FRAGMENT_SHADER);
}

void Plane::draw() {
//    print("draw plane");
}
