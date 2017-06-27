#pragma once
#include "Scene.h"
#include <vector>

static const uint32_t MAX_VERTEX_BUFFER_SIZE = 1000000;
static const uint32_t MAX_INDEX_COUNT = 10000;

class Control;
class Layout;
class Batch2D;
class VertexBuffer;
class IndexBuffer;

class Scene2D : public Scene {

public:
    Scene2D();
    ~Scene2D();
    void draw(float dt) override final;
    void setRootControl(std::shared_ptr<Control> root);

protected:
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;

private:
    void onWindowResize(int width, int height) override;

    std::shared_ptr<Control> root;
    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::unique_ptr<Batch2D>> batches;
};
