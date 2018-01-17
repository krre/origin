#pragma once
#include "Core/Singleton.h"
#include "Graphics/GpuBuffer.h"

namespace Origin {

class RenderWindow;
class Renderer;
class Texture;
class ShaderProgram;

class RenderContext : public Singleton<RenderContext> {

public:
    RenderContext();
    virtual ~RenderContext();
    void init();
    void shutdown();
    virtual std::shared_ptr<RenderWindow> createRenderWindow() = 0;
    virtual std::shared_ptr<GpuBuffer> createGpuBuffer(GpuBuffer::Usage usage, uint32_t size) = 0;
    virtual std::shared_ptr<Texture> createTexture(const std::string& path) = 0;
    virtual std::shared_ptr<ShaderProgram> createShaderProgram() = 0;

    Renderer* getRenderer() const;

protected:
    virtual std::shared_ptr<Renderer> createRenderer() = 0;

private:
    std::shared_ptr<Renderer> renderer;

};

} // Origin
