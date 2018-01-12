#pragma once
#include "Core/Singleton.h"

namespace Origin {

class RenderWindow;
class Renderer;

class RenderContext : public Singleton<RenderContext> {

public:
    RenderContext();
    virtual ~RenderContext();
    void init();
    void shutdown();
    virtual std::shared_ptr<RenderWindow> createRenderWindow() = 0;

    Renderer* getRenderer() const;

protected:
    virtual std::shared_ptr<Renderer> createRenderer() = 0;

private:
    std::shared_ptr<Renderer> renderer;

};

} // Origin
