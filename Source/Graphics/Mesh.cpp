#include "Mesh.h"
#include <assert.h>

Mesh::Mesh() : VBO(GL_ARRAY_BUFFER) {

}

void Mesh::setup() {
    VAO.bind();
    VBO.bind();
    assert(verticles.size());
    VBO.setData(&verticles[0], verticles.size() * sizeof(verticles[0]));

    glVertexAttribPointer(
       0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    VAO.unbind();
}

void Mesh::setShaderGroup(ShaderGroup* shaderGroup) {
    this->shaderGroup = shaderGroup;
}

void Mesh::draw(float dt) {
    shaderGroup->use();
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticles.size());
    VAO.unbind();
}
