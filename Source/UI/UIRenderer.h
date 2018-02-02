#pragma once
#include "Core/Common.h"
#include "UIBatch.h"

namespace Origin {

class RenderPassUI;

class UIRenderer {

public:
    UIRenderer();
    ~UIRenderer();
    void addBatch(UIBatch batch);
    void drawBatches();
    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }
    RenderPassUI* getRenderPassUI() const { return renderPassUI.get(); }

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    std::unique_ptr<RenderPassUI> renderPassUI;
};

} // Origin
