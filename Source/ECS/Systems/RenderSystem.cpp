#include "RenderSystem.h"
#include "../../Debug/Console.h"
#include "../../Debug/DebugHUD.h"
#include "../Core/App.h"
#include "../UI/Toast.h"
#include "../ECS/Engine.h"
#include "../ECS/Components/MeshComponent.h"

RenderSystem::RenderSystem() {
    type = SystemType::Render;
    // Order important!
    // From bottom layer to top
    drawables.push_back(Console::getInstance());
    drawables.push_back(DebugHUD::getInstance());
    drawables.push_back(Toast::getInstance());
}

void RenderSystem::process(float dt) {
    // TODO: Replace by family
    std::vector<Entity*> renderEntities;
    for (auto entity : Engine::getInstance()->getEntities()) {
        Component* meshComp = entity->getComponent(ComponentType::Mesh);
        Component* materialComp = entity->getComponent(ComponentType::Material);
        Component* nodeComp = entity->getComponent(ComponentType::Node);
        if (meshComp && materialComp && nodeComp) {
            renderEntities.push_back(entity);
        }
    }

    renderer.setEntities(&renderEntities);
    renderer.render(dt);

    App::getInstance()->getViewport()->render();
    for (auto drawable : drawables) {
        if (drawable->getVisible()) {
            drawable->draw(dt);
        }
    }
}
