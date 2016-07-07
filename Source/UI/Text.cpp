#include "Text.h"
#include "../Core/App.h"
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
}

void Text::setText(const string& text) {
    this->text = text;
}
