#pragma once
#include "UI/Control.h"

namespace Origin {

class RenderPassResource;

class Screen : public Control {

public:

    enum class Name {
        Menu,
        Settings,
        Game
    };

    Screen();
    virtual ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    const std::vector<RenderPassResource*>& getRenderPassResources() const { return renderPassResources; }

protected:
    std::vector<RenderPassResource*> renderPassResources;

private:
    void updateImpl(float dt) override;
    void drawImpl() override;
    void postDraw() override;

    bool isPaused = true;
};

} // Origin
