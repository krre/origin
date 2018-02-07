#pragma once
#include "UI/Control.h"

namespace Origin {

class UIManager;
class UIRenderer;
class EntityManager;
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

    UIManager* getUIManager() const { return uiManager.get(); }
    UIRenderer* getUIRenderer() const { return uiRenderer.get(); }
    EntityManager* getEntityEngine() const { return entityManager.get(); }

    const std::vector<RenderPassResource*>& getRenderPassResources() const { return renderPassResources; }

protected:
    std::vector<RenderPassResource*> renderPassResources;

private:
    void updateImpl(float dt) override;
    void drawImpl() override;
    void postDraw() override;

    bool isPaused = true;
    std::unique_ptr<UIManager> uiManager;
    std::unique_ptr<UIRenderer> uiRenderer;
    std::unique_ptr<EntityManager> entityManager;
};

} // Origin
