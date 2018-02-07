#pragma once
#include "Core/Common.h"
#include "Core/Singleton.h"

namespace Origin {

class UIManager;
class UIRenderer;
class EntityManager;

class Context : public Singleton<Context> {

public:
    Context();
    ~Context();

    UIManager* getUIManager() const { return uiManager.get(); }
    UIRenderer* getUIRenderer() const { return uiRenderer.get(); }
    EntityManager* getEntityManager() const { return entityManager.get(); }

private:
    std::unique_ptr<UIManager> uiManager;
    std::unique_ptr<UIRenderer> uiRenderer;
    std::unique_ptr<EntityManager> entityManager;
};

} // Origin
