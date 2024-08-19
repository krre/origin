#pragma once
#include <core/Object.h>

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseButtonEvent;

class UIBatch;
class VertexBuffer;
class IndexBuffer;
class Screen;
class Layout;
class UIManager;

class Control : public Core::Object {
    friend class Renderer;
    friend class UIManager;
public:
    Control(Control* parent = nullptr);

    void setPosition(const Core::Pos2& position);
    const Core::Pos2& position() const { return m_position; }

    const Core::Pos2& absolutePosition() const { return m_absolutePosition; }

    void updatePosition();

    const Core::Size& size() const { return m_size; }
    void setSize(const Core::Size& size);

    int contentWidth() const { return m_size.width ? m_size.width : m_contentWidth; }
    int contentHeight() const { return m_size.height ? m_size.height : m_contentHeight; }

    void setScale(float scale);
    float scale() const { return m_scale; }

    void resize(int width, int height);
    void move(int x, int y);

    void markDirty();
    void clearDirty();
    bool dirty() const { return m_dirty; }

    void setVisible(bool visible);
    bool visible() const { return m_visible; }

    void update(float dt);
    void draw();

    void activate();

protected:
    virtual void resizeImpl(int width, int height) {}
    virtual void updateImpl(float dt) {}
    virtual void drawImpl() {}
    virtual void postDraw() {}
    virtual void keyPressed(const SDL_KeyboardEvent& event) {}
    virtual void textPressed(const SDL_TextInputEvent& event) {}
    virtual void mouseButtonAction(const SDL_MouseButtonEvent& event) {}

    UIManager* m_uiManager = nullptr;
    Core::Pos2 m_position = { 0, 0 };
    Core::Pos2 m_absolutePosition = { 0, 0 };
    Core::Size m_size = { 0, 0 };
    int m_contentWidth = 0;
    int m_contentHeight = 0;
    float m_scale = 1.0;
    bool m_visible = true;

private:
    bool m_dirty = true;
};
