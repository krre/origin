#include "Text.h"
#include "../Core/App.h"
#include "../Graphics/OpenGL/Shader.h"
#include <GL/glew.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

Text::Text() {
    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
    }

    FT_Face face;

    string fontPath = App::getAbsolutePath() + "/Data/Fonts/arial.ttf";
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        fprintf(stderr, "Could not open font\n");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        fprintf(stderr, "Could not load character 'X'\n");
    }

    FT_GlyphSlot g = face->glyph;

    Shader fontVertexShader(GL_VERTEX_SHADER);
    fontVertexShader.load("Font.vert");

    Shader fontFragmentShader(GL_FRAGMENT_SHADER);
    fontFragmentShader.load("Font.frag");

    fontProgram.addShader(fontVertexShader);
    fontProgram.addShader(fontFragmentShader);
    fontProgram.link();
}

void Text::setText(const string& text) {
    this->text = text;
}

void Text::render(float dt) {
    fontProgram.use();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
