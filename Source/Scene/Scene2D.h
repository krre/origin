#pragma once
#include "Scene.h"
#include <vector>

namespace Vulkan {
    class GpuBuffer;
}

namespace Origin {

static const uint32_t MAX_VERTEX_BUFFER_SIZE = 1000000;
static const uint32_t MAX_INDEX_COUNT = 10000;

class Control;
class Layout;
class Batch2D;

class Scene2D : public Scene {

public:
    Scene2D();
    ~Scene2D();
    void render(float dt);

protected:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> indexBuffer;

private:
    void onWindowResize(int width, int height) override;

    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::unique_ptr<Batch2D>> batches;
};

} // Origin
