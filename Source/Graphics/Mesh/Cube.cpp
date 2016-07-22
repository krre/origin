#include "Cube.h"

Cube::Cube(float width, float height, float depth) :
    width(width), height(height), depth(depth) {

    GLfloat vertexData[] = {
        -1.0f * width, -1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,
         1.0f * width, -1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,
         1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,
         1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,
        -1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,
        -1.0f * width, -1.0f * height, -1.0f * depth,  0.0f,  0.0f, -1.0f,

        -1.0f * width, -1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,
         1.0f * width, -1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,
         1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,
         1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,
        -1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,
        -1.0f * width, -1.0f * height,  1.0f * depth,  0.0f,  0.0f,  1.0f,

        -1.0f * width,  1.0f * height,  1.0f * depth, -1.0f,  0.0f,  0.0f,
        -1.0f * width,  1.0f * height, -1.0f * depth, -1.0f,  0.0f,  0.0f,
        -1.0f * width, -1.0f * height, -1.0f * depth, -1.0f,  0.0f,  0.0f,
        -1.0f * width, -1.0f * height, -1.0f * depth, -1.0f,  0.0f,  0.0f,
        -1.0f * width, -1.0f * height,  1.0f * depth, -1.0f,  0.0f,  0.0f,
        -1.0f * width,  1.0f * height,  1.0f * depth, -1.0f,  0.0f,  0.0f,

         1.0f * width,  1.0f * height,  1.0f * depth,  1.0f,  0.0f,  0.0f,
         1.0f * width,  1.0f * height, -1.0f * depth,  1.0f,  0.0f,  0.0f,
         1.0f * width, -1.0f * height, -1.0f * depth,  1.0f,  0.0f,  0.0f,
         1.0f * width, -1.0f * height, -1.0f * depth,  1.0f,  0.0f,  0.0f,
         1.0f * width, -1.0f * height,  1.0f * depth,  1.0f,  0.0f,  0.0f,
         1.0f * width,  1.0f * height,  1.0f * depth,  1.0f,  0.0f,  0.0f,

        -1.0f * width, -1.0f * height, -1.0f * depth,  0.0f, -1.0f,  0.0f,
         1.0f * width, -1.0f * height, -1.0f * depth,  0.0f, -1.0f,  0.0f,
         1.0f * width, -1.0f * height,  1.0f * depth,  0.0f, -1.0f,  0.0f,
         1.0f * width, -1.0f * height,  1.0f * depth,  0.0f, -1.0f,  0.0f,
        -1.0f * width, -1.0f * height,  1.0f * depth,  0.0f, -1.0f,  0.0f,
        -1.0f * width, -1.0f * height, -1.0f * depth,  0.0f, -1.0f,  0.0f,

        -1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  1.0f,  0.0f,
         1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  1.0f,  0.0f,
         1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  1.0f,  0.0f,
         1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  1.0f,  0.0f,
        -1.0f * width,  1.0f * height,  1.0f * depth,  0.0f,  1.0f,  0.0f,
        -1.0f * width,  1.0f * height, -1.0f * depth,  0.0f,  1.0f,  0.0f
    };

    verticles = std::vector<GLfloat>(vertexData, vertexData + sizeof vertexData / sizeof vertexData[0]);
    setup();
}
