#include "Rectangle.h"
#include "../Core/App.h"
#include "../Resource/ResourceManager.h"
#include <glm/ext.hpp>

Rectangle::Rectangle(int width, int height) :
    Control(width, height),
    plane(1.0, 1.0) {
    baseShaderGroup = ResourceManager::getInstance()->getShaderGroup("BaseShaderGroup");
}

void Rectangle::draw(float dt) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(position.x + width / 2.0f, z, position.y + height / 2.0f - App::getInstance()->getHeight()));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(width, 1.0, height));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 model = rotationMatrix * translationMatrix * scaleMatrix;
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(App::getInstance()->getWidth()), 0.0f, static_cast<GLfloat>(App::getInstance()->getHeight()));
    glm::mat4 mvp = projection * model;
    baseShaderGroup->bind();
    glUniformMatrix4fv(glGetUniformLocation(baseShaderGroup->getProgram(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3f(glGetUniformLocation(baseShaderGroup->getProgram(), "color"), color.x, color.y, color.z);
    plane.draw();
}

void Rectangle::setColor(const glm::vec3& color) {
    this->color = color;
}
