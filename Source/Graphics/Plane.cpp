#include "Plane.h"

Plane::Plane(float width, float height) : width(width), height(height) {
//    GLfloat vertexData[] = {
//        -1.0f * width, 0.0f, -1.0f * height, 0.0f, 1.0f, 0.0f,
//         1.0f * width, 0.0f,  1.0f * height, 0.0f, 1.0f, 0.0f,
//         1.0f * width, 0.0f, -1.0f * height, 0.0f, 1.0f, 0.0f,

//        -1.0f * width, 0.0f, -1.0f * height, 0.0f, 1.0f, 0.0f,
//        -1.0f * width, 0.0f,  1.0f * height, 0.0f, 1.0f, 0.0f,
//         1.0f * width, 0.0f,  1.0f * height, 0.0f, 1.0f, 0.0f,
//    };

//    verticles = std::vector<GLfloat>(vertexData, vertexData + sizeof vertexData / sizeof vertexData[0]);
    setup();
}