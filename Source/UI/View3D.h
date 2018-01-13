#pragma once
#include "View.h"

namespace Origin {

class View3D : public View {

public:
    View3D();
    Dimension getDimension() const override;
    void prepareBatch(std::vector<Batch2D>& batches, std::vector<float>& vertices) override;
};

} // Origin
