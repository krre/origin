#pragma once
#include "Core/Object.h"
#include "UIBatch.h"

namespace Origin {

class RenderPassUI;

class UIRenderer : public Object {

public:
    UIRenderer(Object* parent = nullptr);
    ~UIRenderer();
    void addBatch(UIBatch batch);
    void drawBatches();
    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }
    RenderPassUI* getRenderPassUI() const { return renderPassUI; }

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    RenderPassUI* renderPassUI;
};

} // Origin
