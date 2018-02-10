#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>
#include <vector>
#include "UIBatch.h"

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;

namespace Origin {

class UIBatch;
class VertexBuffer;
class IndexBuffer;
class Screen;
class Layout;
class UIManager;

class Control : public Object {
    friend class Renderer;
    friend class UIManager;

public:
    Control(Control* parent = nullptr);
    virtual ~Control();

    void setPosition(const Pos2& position);
    const Pos2& getPosition() const { return position; }

    const Pos2& getAbsolutePosition() const { return absolutePosition; }

    void updatePosition();

    const Size& getSize() const { return size; }
    void setSize(const Size& size);

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

    void setLayout(Layout* layout);
    Layout* getLayout() const { return layout; }

    void activate();

protected:
    virtual void resizeImpl(int width, int height) {}
    virtual void updateImpl(float dt) {}
    virtual void drawImpl() {}
    virtual void postDraw() {}
    virtual void keyPressed(const SDL_KeyboardEvent& event) {}
    virtual void textPressed(const SDL_TextInputEvent& event) {}

    UIManager* uiManager;
    Layout* layout = nullptr;
    Pos2 position = { 0, 0 };
    Pos2 absolutePosition = { 0, 0 };
    Size size = { 0, 0 };
    int contentWidth = 0;
    int contentHeight = 0;
    float scale = 1.0;
    bool visible = true;

private:
    bool dirty = true;
};

} // Origin
