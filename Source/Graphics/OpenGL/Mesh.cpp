#include "Mesh.h"
#include <assert.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Mesh::Mesh() : vbo(GL_ARRAY_BUFFER) {

}

void Mesh::setup() {
    assert(verticles.size());
    vao.bind();
    vbo.bind();
    vbo.setData(&verticles[0], verticles.size() * sizeof(verticles[0]));

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    vao.unbind();
}

void Mesh::draw() {
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticles.size() / 6);
    vao.unbind();
}
