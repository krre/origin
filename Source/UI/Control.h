#pragma once
#include "Core/Object.h"

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
    virtual ~Control();

    void setPosition(const Core::Pos2& position);
    const Core::Pos2& getPosition() const { return position; }

    const Core::Pos2& getAbsolutePosition() const { return absolutePosition; }

    void updatePosition();

    const Core::Size& getSize() const { return size; }
    void setSize(const Core::Size& size);

    int getContentWidth() const { return size.width ? size.width : contentWidth; }
    int getContentHeight() const { return size.height ? size.height : contentHeight; }

    void setScale(float scale);
    float getScale() const { return scale; }

    void resize(int width, int height);
    void move(int x, int y);

    void markDirty();
    void clearDirty();
    bool getDirty() const { return dirty; }

    void setVisible(bool visible);
    bool getVisible() const { return visible; }

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

    UIManager* uiManager;
    Core::Pos2 position = { 0, 0 };
    Core::Pos2 absolutePosition = { 0, 0 };
    Core::Size size = { 0, 0 };
    int contentWidth = 0;
    int contentHeight = 0;
    float scale = 1.0;
    bool visible = true;

private:
    bool dirty = true;
};
