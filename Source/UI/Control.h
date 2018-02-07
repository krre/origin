#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>
#include <vector>
#include "UIBatch.h"

namespace Origin {

class UIBatch;
class VertexBuffer;
class IndexBuffer;
class Screen;
class Layout;

class Control : public Object {
    friend class Renderer;

public:
    Control(Control* parent = nullptr);
    virtual ~Control();

    void setPosition(const Pos2& position);
    const Pos2& getPosition() const { return position; }
    const Pos2& getAbsolutePosition() const { return absolutePosition; }

    const Size& getSize() const { return size; }
    void setSize(const Size& size);

    void setScale(float scale);
    float getScale() const { return scale; }

    void resize(int width, int height);

    void markDirty();
    void clearDirty();
    bool getDirty() const { return dirty; }

    void setVisible(bool visible);
    bool getVisible() const { return visible; }

    void update(float dt);
    void draw();

    void setParent(Control* parent);
    void addChild(Control* control);
    void removeChild(Control* control);
    void removeChildren();
    const std::vector<Control*>& getChildren() const { return children; }

    void setScreen(Screen* screen);
    Screen* getScreen() const { return screen; }

    void setLayout(Layout* layout);
    Layout* getLayout() const { return layout; }

protected:
    virtual void updateImpl(float dt) {}
    virtual void drawImpl() {}
    virtual void postDraw() {}

    Control* parent = nullptr;
    Screen* screen = nullptr;
    std::vector<Control*> children;
    Pos2 position = { 0, 0 };
    Pos2 absolutePosition = { 0, 0 };
    Size size;
    float scale = 1.0;
    bool visible = true;

private:
    Layout* layout = nullptr;
    bool dirty = true;
};

} // Origin
