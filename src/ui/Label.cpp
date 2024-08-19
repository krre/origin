#include "Label.h"
#include "resource/ResourceManager.h"
#include "Font.h"
#include "graphics/render/UIRenderer.h"
#include "UIBatch.h"

Label::Label(Control* parent) : Control(parent) {
    setFont(ResourceManager::get()->load<Font>("fonts/inconsolatalgc.ttf"));
}

Label::Label(const std::string& text, Control* parent) : Label(parent) {
    setText(text);
}

void Label::setText(const std::string& text) {
    if (m_text.length() != text.length()) {
        // Causes undesirable rebuild Vulkan command buffers
//        markDirty();
    }
    m_text = text;

    m_contentWidth = 0;
    m_contentHeight = 0;
    m_lineCount = text.length() ? 1 : 0;
    int lineWidth = 0;
    int maxLineWidth = 0;
    int maxLineHeight = 0;

    for (auto& sign : text) {
        Font::GlyphInfo& glyphInfo = m_font->gliphInfo((int)sign);
        lineWidth += glyphInfo.advanceX;
        maxLineHeight = std::max(maxLineHeight, glyphInfo.offsetY);

        // New line
        if (sign == '\n') {
            m_lineCount++;
            maxLineWidth = std::max(maxLineWidth, lineWidth);
        }
    }

    if (m_lineCount == 1) {
        m_contentWidth = lineWidth;
        m_contentHeight = maxLineHeight;
    } else if (m_lineCount > 1) {
        m_contentWidth = maxLineWidth;
        m_contentHeight = m_font->lineHeight() * m_lineCount;
    }
}

void Label::setFont(Font* font) {
    m_font = font;
}

void Label::setColor(const Color& color) {
    m_color = color;
}

void Label::drawImpl() {
    UIBatch batch(UIRenderer::get()->verticles());
    batch.color = m_color;
    batch.texture = m_font->texture();
    batch.addText(m_absolutePosition.x, m_absolutePosition.y, m_text, m_font);
    UIRenderer::get()->addBatch(batch);
}
