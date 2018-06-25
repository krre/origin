#pragma once
#include "Renderer.h"
#include "UI/UIBatch.h"

namespace Origin {

class RenderLayerUI;

class UIRenderer : public Renderer {

public:
    UIRenderer(Object* parent = nullptr);
    ~UIRenderer();

    static UIRenderer* get();

    void draw() override;
    RenderLayer* getRenderLayer() const override;

    void addBatch(UIBatch batch);
    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    RenderLayerUI* renderLayerUI;
};

} // Origin
