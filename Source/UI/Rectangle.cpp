#include "Rectangle.h"
#include "../Resource/ResourceManager.h"

Rectangle::Rectangle(int width, int height) :
    Control(width, height),
    plane(1.0, 1.0) {
    baseShaderGroup = ResourceManager::getInstance()->getShaderGroup("BaseShaderGroup");
}

void Rectangle::draw(float dt) {
    glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
    glUniformMatrix4fv(glGetUniformLocation(baseShaderGroup->getProgram(), "mvp"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(baseShaderGroup->getProgram(), "color"), color.x, color.y, color.z);
    baseShaderGroup->use();
    plane.draw();
}

void Rectangle::setColor(const glm::vec3& color) {
    this->color = color;
}
