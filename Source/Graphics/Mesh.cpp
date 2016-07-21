#include "Mesh.h"
#include <assert.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Mesh::Mesh() : VBO(GL_ARRAY_BUFFER) {

}

void Mesh::setup() {
    assert(verticles.size());
    VAO.bind();
    VBO.bind();
    VBO.setData(&verticles[0], verticles.size() * sizeof(verticles[0]));

    glVertexAttribPointer(
       0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    VAO.unbind();
}

void Mesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticles.size() / 3);
    VAO.unbind();
}
