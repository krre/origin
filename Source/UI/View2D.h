#pragma once
#include "View.h"

class View2D : public View {

public:
    View2D();
    ~View2D();
    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
};
