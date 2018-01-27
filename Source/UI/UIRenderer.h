#pragma once
#include "Core/Common.h"
#include "UIBatch.h"

namespace Vulkan {
    class GpuBuffer;
}

namespace Origin {

class UIRenderer {

public:
    UIRenderer();
    ~UIRenderer();
    void addBatch(UIBatch batch);
    void drawBatches();
    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
};

} // Origin
