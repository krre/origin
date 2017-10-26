#pragma once
#include "Control.h"

class View2D : public Control {

public:
    View2D();
    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
};
