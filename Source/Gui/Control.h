#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>
#include <vector>
#include "Gui/Batch2D.h"

namespace Origin {

class Batch2D;
class VertexBuffer;
class IndexBuffer;
class Screen;

class Control : public Object {
    friend class Renderer;

public:
    Control(Control* parent = nullptr);
    ~Control();

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

    virtual void prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {}

protected:
    virtual void updateImpl(float dt) {}
    virtual void drawImpl() {}

    Control* parent = nullptr;
    std::vector<Control*> children;
    Pos2 position = { 0, 0 };
    Pos2 absolutePosition = { 0, 0 };
    Size size;
    float scale = 1.0;
    bool visible = true;

private:
    Screen* screen = nullptr;
    bool isDirty = true;
};

} // Origin
