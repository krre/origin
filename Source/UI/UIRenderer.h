#pragma once
#include "Core/Common.h"
#include "Batch2D.h"

namespace Vulkan {
    class GpuBuffer;
}

namespace Origin {

class UIRenderer {

public:
    UIRenderer();
    ~UIRenderer();
    void addBatch(Batch2D batch);
    void drawBatches();
    std::vector<Batch2D::Vertex>* getVerticles() { return &vertices; }

private:
    std::vector<Batch2D> batches;
    std::vector<Batch2D::Vertex> vertices;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
};

} // Origin
