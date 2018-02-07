#include "Context.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "ECS/EntityManager.h"

namespace Origin {

Context::Context() {
    uiManager = std::make_unique<UIManager>();
    uiRenderer = std::make_unique<UIRenderer>();
    entityManager = std::make_unique<EntityManager>();
}

Context::~Context() {

}

} // Origin
