#pragma once
#include "View.h"

namespace Origin {

class View2D : public View {

public:
    View2D();
    ~View2D();
    Dimension getDimension() const override;
    void prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) override;

};

} // Origin
