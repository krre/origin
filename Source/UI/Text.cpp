#include "Text.h"
#include "../Core/App.h"
#include "../Graphics/OpenGL/Shader.h"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Text::Text() {
    color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
    }

    FT_Face face;

//    string fontPath = App::getAbsolutePath() + "/Data/Fonts/arial.ttf";
    string fontPath = App::getAbsolutePath() + "/Data/Fonts/inconsolatalgc.ttf";
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        fprintf(stderr, "Could not open font\n");
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    Shader fontVertexShader(GL_VERTEX_SHADER);
    fontVertexShader.load("Font.vert");

    Shader fontFragmentShader(GL_FRAGMENT_SHADER);
    fontFragmentShader.load("Font.frag");

    fontProgram.addShader(fontVertexShader);
    fontProgram.addShader(fontFragmentShader);
    fontProgram.link();
    fontProgram.use();
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte i = 0; i < 128; i++) {
        // Load character glyph
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
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
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(i, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::setText(const string& text) {
    this->text = text;
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

void Text::render(float dt) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    fontProgram.use();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(App::getInstance()->getWidth()), 0.0f, static_cast<GLfloat>(App::getInstance()->getHeight()));
    glUniformMatrix4fv(glGetUniformLocation(fontProgram.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(fontProgram.getId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vao);

    // Iterate through all characters
    GLfloat startX = position.x;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        GLfloat xpos = startX + ch.bearing.x * scale;
        GLfloat ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

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
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        startX += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}
