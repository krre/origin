#include "Rectangle.h"
#include "../Core/App.h"
#include "../Resource/ResourceManager.h"
#include <glm/ext.hpp>

Rectangle::Rectangle(int width, int height) :
    Control(width, height),
    plane(1.0, 1.0) {
//    baseShaderGroup = ResourceManager::get()->getResource<ShaderGroup>("BaseShaderGroup");
}

void Rectangle::draw(float dt) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(position.x + size.width / 2.0f, z, position.y + size.height / 2.0f - App::get()->getHeight()));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(size.width, 1.0, size.height));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 model = rotationMatrix * translationMatrix * scaleMatrix;
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(App::get()->getWidth()), 0.0f, static_cast<GLfloat>(App::get()->getHeight()));
//    glm::mat4 mvp = projection * model;
//    baseShaderGroup->bind();
//    glUniformMatrix4fv(glGetUniformLocation(baseShaderGroup->getProgram(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
//    glUniform3f(glGetUniformLocation(baseShaderGroup->getProgram(), "color"), color.x, color.y, color.z);
    plane.draw();
}

void Rectangle::update(float dt) {

}

void Rectangle::setColor(const glm::vec3& color) {
    this->color = color;
}
