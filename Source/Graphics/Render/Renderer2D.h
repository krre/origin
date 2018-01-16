#pragma once
#include "Core/Common.h"
#include "Gui/Batch2D.h"

namespace Origin {

class Control;
class View3D;

class Renderer2D {

public:
    Renderer2D();
    virtual ~Renderer2D();
    void render(Control* control);

private:
    void getBatches(Control* control, std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices);

    std::vector<Batch2D> batches;
    std::vector<Batch2D::Vertex> vertices;
    std::vector<View3D*> renderViews;
};

} // Origin
