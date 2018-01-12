#pragma once
#include "View.h"

namespace Origin {

class View3D : public View {

public:
    View3D();
    Dimension getDimension() const override;
    void prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) override;
};

} // Origin
