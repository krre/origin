#include "Text.h"
#include "../../Core/App.h"
#include "../../Resource/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Text::Text() {
    setFont(ResourceManager::get()->getResource<Font>("InconsolataFont"));
}

void Text::setText(const std::string& text) {
    this->text = text;
    updateTextData();
}

void Text::setFont(Font* font) {
    this->font = font;
}

void Text::setColor(const glm::vec3& color) {
    this->color = color;
}

void Text::draw(float dt) {
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    fontShaderGroup->bind();

//    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, z));
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(App::get()->getWidth()), 0.0f, static_cast<GLfloat>(App::get()->getHeight())) * translationMatrix;
//    glUniformMatrix4fv(glGetUniformLocation(fontShaderGroup->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

//    glUniform3f(glGetUniformLocation(fontShaderGroup->getProgram(), "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);

//    glBindVertexArray(vao);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    // Iterate through all characters
//    GLfloat startX = position.x;
//    // TODO: Move relative coordinates on top level
//    float y = App::get()->getHeight() - position.y;
//    for (auto c: text) {
//        Character ch = characters[c];

//        GLfloat xpos = startX + ch.bearing.x * scale;
//        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

//        GLfloat w = ch.size.x * scale;
//        GLfloat h = ch.size.y * scale;

//        // Update VBO for each character
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos,     ypos,       0.0, 1.0 },
//            { xpos + w, ypos,       1.0, 1.0 },

//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//            { xpos + w, ypos + h,   1.0, 0.0 }
//        };

//        // Render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.textureId);

//        // Update content of VBO memory
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

//        // Render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        startX += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//    }

//    glBindTexture(GL_TEXTURE_2D, 0);
    //    glDisable(GL_BLEND);
}

void Text::update(float dt) {

}

void Text::updateTextData() {

}
