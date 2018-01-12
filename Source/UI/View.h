#pragma once
#include "Control.h"

namespace Origin {

namespace Vulkan {
    class Device;
    class CommandBuffer;
}

class View : public Control {

public:

    enum class Dimension {
        View2D,
        View3D
    };

    View();
    ~View();
    virtual Dimension getDimension() const = 0;
    void update(float dt);
    void render();
    const std::vector<View*> getInnerViews();
    virtual void writeCommands(Vulkan::CommandBuffer* commandBuffer) = 0;

protected:
    Vulkan::Device* device;

private:
    std::vector<View*> innerViews;
};

} // Origin
