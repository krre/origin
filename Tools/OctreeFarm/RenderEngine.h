#pragma once
#include "Vulkan/Renderer.h"
#include <QObject>

namespace OctreeFarm {

class RenderEngine : public QObject, public Vulkan::Renderer {
    Q_OBJECT

public:
    RenderEngine(void* platformHandle, void* platformWindow, QObject* parent = nullptr);
    virtual ~RenderEngine();

private:
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // OctreeFarm
