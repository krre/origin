#pragma once
#include "Control.h"

class View3D : public Control {

public:
    View3D();
    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
};
