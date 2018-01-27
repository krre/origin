#pragma once
#include "Core/Common.h"
#include "UI/UIBatch.h"

namespace Vulkan {
    class GpuBuffer;
}

namespace Origin {

class Control;
class View3D;

class Renderer2D {

public:
    Renderer2D();
    virtual ~Renderer2D();
    void render();
    void prepare(Control* control);
    std::vector<View3D*> getRenderViews() const { return renderViews; }

private:
    void getBatches(Control* control, std::vector<UIBatch>& batches, std::vector<UIBatch::Vertex>& vertices);

    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    std::vector<View3D*> renderViews;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
};

} // Origin
