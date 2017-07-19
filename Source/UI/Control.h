#pragma once
#include "Graphics/Drawable.h"
#include "Core/Node.h"
#include <glm/glm.hpp>
#include <vector>

class Batch2D;
class VertexBuffer;
class IndexBuffer;

class Control : public Origin::Drawable, public Node {

public:
    Control(const Pos2& position = {});

    void setX(int x);
    void setY(int y);

    void setPosition(const Pos2& position);
    const Pos2& getPosition() const { return position; }
    const Pos2& getAbsolutePosition() const { return absolutePosition; }

    const Size& getSize() const { return size; }
    void setSize(const Size& size);

    void setScale(float scale);
    float getScale() const { return scale; }

    void setFillControl(Control* fillControl);
    void setCenterControl(Control* centerControl);

    void resize(int width, int height);

    float getZ() const { return z; }
    void setZ(float z);

    void markDirty();
    void clearDirty();

    void getBatches(std::vector<std::unique_ptr<Batch2D>>& batches, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
    virtual void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) = 0;

protected:
    Pos2 position = { 0, 0 };
    Pos2 absolutePosition = { 0, 0 };
    Size size;
    float scale = 1.0;
    float z = 0.0f;

private:
    Control* fillControl = nullptr;
    Control* centerControl = nullptr;
    bool isDirty = true;
};
