#include "Label.h"
#include "Resource/ResourceManager.h"
#include "Font.h"
#include "Graphics/Render/UIRenderer.h"
#include "UIBatch.h"

Label::Label(Control* parent) : Control(parent) {
    setFont(ResourceManager::get()->load<Font>("Fonts/inconsolatalgc.ttf"));
}

Label::Label(const std::string& text, Control* parent) : Label(parent) {
    setText(text);
}

void Label::setText(const std::string& text) {
    if (this->text.length() != text.length()) {
        // Causes undesirable rebuild Vulkan command buffers
//        markDirty();
    }
    this->text = text;

    contentWidth = 0;
    contentHeight = 0;
    lineCount = text.length() ? 1 : 0;
    int lineWidth = 0;
    int maxLineWidth = 0;
    int maxLineHeight = 0;

    for (auto& sign : text) {
        Font::GlyphInfo& glyphInfo = font->getGliphInfo((int)sign);
        lineWidth += glyphInfo.advanceX;
        maxLineHeight = std::max(maxLineHeight, glyphInfo.offsetY);

        // New line
        if (sign == '\n') {
            lineCount++;
            maxLineWidth = std::max(maxLineWidth, lineWidth);
        }
    }

    if (lineCount == 1) {
        contentWidth = lineWidth;
        contentHeight = maxLineHeight;
    } else if (lineCount > 1) {
        contentWidth = maxLineWidth;
        contentHeight = font->getLineHeight() * lineCount;
    }
}

void Label::setFont(Font* font) {
    this->font = font;
}

void Label::setColor(const Color& color) {
    this->color = color;
}

void Label::drawImpl() {
    UIBatch batch(UIRenderer::get()->getVerticles());
    batch.color = color;
    batch.texture = font->getTexture();
    batch.addText(absolutePosition.x, absolutePosition.y, text, font);
    UIRenderer::get()->addBatch(batch);
}
