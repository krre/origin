#include "Mesh.h"
#include "../Core/App.h"
#include "../ECS/Engine.h"
#include "../ECS/Systems/CameraSystem.h"
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

void Mesh::setShaderGroup(ShaderGroup* shaderGroup) {
    this->shaderGroup = shaderGroup;
}

void Mesh::draw(float dt) {
    shaderGroup->use();

    GLuint matrix = glGetUniformLocation(shaderGroup->getProgram(), "mvp");
    CameraSystem* cameraSystem = static_cast<CameraSystem*>(Engine::getInstance()->getSystem(System::Type::Camera).get());
    glm::mat4 projection = cameraSystem->getProjection(App::getInstance()->getViewport()->getCurrentCamera().get());
    glm::mat4 view = cameraSystem->getView(App::getInstance()->getViewport()->getCurrentCamera().get());
    glm::mat4 modelMatrix(1.0f);
    glm::mat4 mvp = projection * view * modelMatrix;
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    GLuint color = glGetUniformLocation(shaderGroup->getProgram(), "color");
    glm::vec3 c(0.2, 0.7, 0.8);
    glUniform3fv(color, 1, &c[0]);

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticles.size() / 3);
    VAO.unbind();
}
