#pragma once
#include "Control.h"

namespace Origin {

namespace Vulkan {
    class Device;
    class CommandBuffer;
}

class Scene;

class View : public Control {

public:
    View();
    ~View();
    void update(float dt);
    void render();
    Scene* getScene() const { return scene.get(); }
    const std::vector<View*> getInnerViews();
    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;

protected:
    Vulkan::Device* device;

private:
    std::vector<View*> innerViews;
    std::unique_ptr<Scene> scene;
};

} // Origin
