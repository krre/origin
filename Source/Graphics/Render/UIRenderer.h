#pragma once
#include "Renderer.h"
#include "UI/UIBatch.h"

namespace Origin {

class RenderPassUI;

class UIRenderer : public Renderer {

public:
    UIRenderer(Object* parent = nullptr);
    ~UIRenderer();

    static UIRenderer* get();

    void draw() override;
    RenderPassResource* getRenderPass() const override;

    void addBatch(UIBatch batch);
    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    RenderPassUI* renderPassUI;
};

} // Origin
