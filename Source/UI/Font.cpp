#include "Font.h"
#include "../Resource/ResourceManager.h"

Font::Font() {

}

Font::~Font() {
//    FT_Done_Face(face);
}

void Font::setSize(int size) {
    this->size = size;

    FT_Set_Pixel_Sizes(face, 0, size);

    characters.clear();

        // Load first 128 characters of ASCII set
        for (uint8_t i = 0; i < 128; i++) {
            // Load character glyph
            if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
                ERROR("Failed to load Glyph");
                continue;
            }

            // Generate texture
    //        GLuint texture;
    //        glGenTextures(1, &texture);
    //        glBindTexture(GL_TEXTURE_2D, texture);
    //        glTexImage2D(
    //            GL_TEXTURE_2D,
    //            0,
    //            GL_RED,
    //            face->glyph->bitmap.width,
    //            face->glyph->bitmap.rows,
    //            0,
    //            GL_RED,
    //            GL_UNSIGNED_BYTE,
    //            face->glyph->bitmap.buffer
    //        );

            // Set texture options
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Now store character for later use
            Glyph character = {
    //            texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (uint32_t)face->glyph->advance.x
            };
            characters.insert(std::pair<char, Glyph>(i, character));
    //        glBindTexture(GL_TEXTURE_2D, 0);
        }

        // Configure VAO/VBO for texture quads
    //    glGenBuffers(1, &vbo);
    //    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    //    glGenVertexArrays(1, &vao);
    //    glBindVertexArray(vao);
    //    glEnableVertexAttribArray(0);
    //    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
}

void Font::load(const std::string& path) {

    if (FT_New_Face(ResourceManager::get()->getFreeTypeHandler(), path.c_str(), 0, &face)) {
        ERROR("Could not open font " << path);
        return;
    }

    setSize(14);
}
