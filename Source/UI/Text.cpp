#include "Text.h"
#include "../Core/App.h"
#include "../Graphics/OpenGL/Shader.h"
#include "../Graphics/OpenGL/Texture.h"
#include "../Resource/ResourceManager.h"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Text::Text() : vbo(GL_ARRAY_BUFFER) {
    color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        error("Could not init freetype library");
    }

    FT_Face face;

    std::string fontPath = App::getAbsolutePath() + "/Data/Fonts/inconsolatalgc.ttf";
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        error("Could not open font " << fontPath);
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    fontShaderGroup = ResourceManager::getInstance()->getShaderGroup("FontShaderGroup");
    fontShaderGroup->use();
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte i = 0; i < 128; i++) {
        // Load character glyph
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            error("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }

        // Generate texture
        Texture texture(GL_TEXTURE_2D);
        texture.bind();
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        Character character = {
            texture.getId(),
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(i, character));
        texture.unbind();
    }

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
}

void Text::setText(const std::string& text) {
    this->text = text;
}

void Text::setFont(Font* font) {
    this->font = font;
}

void Text::setColor(const glm::vec4& color) {
    this->color = color;
}

void Text::setScale(float scale) {
    this->scale = scale;
}

void Text::setFontSize(int fontSize) {
    this->fontSize = fontSize;
}

void Text::draw(float dt) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    fontShaderGroup->use();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, z));
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(App::getInstance()->getWidth()), 0.0f, static_cast<GLfloat>(App::getInstance()->getHeight())) * translationMatrix;
    glUniformMatrix4fv(glGetUniformLocation(fontShaderGroup->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(fontShaderGroup->getProgram(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vao);
    vbo.bind();
    // Iterate through all characters
    GLfloat startX = position.x;
    // TODO: Move relative coordinates on top level
    float y = App::getInstance()->getHeight() - position.y;
    for (auto c: text) {
        Character ch = characters[c];

        GLfloat xpos = startX + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);

        // Update content of VBO memory
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        startX += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}
