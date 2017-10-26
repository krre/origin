#pragma once
#include "View.h"

class View3D : public View {

public:
    View3D();
    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
};
