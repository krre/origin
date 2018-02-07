#include "Screen.h"
#include "UI/Control.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "ECS/EntityManager.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
    uiManager = std::make_unique<UIManager>();
    uiRenderer = std::make_unique<UIRenderer>();
    entityManager = std::make_unique<EntityManager>();

    renderPassResources.push_back(uiRenderer->getRenderPassUI());
}

Screen::~Screen() {

}

void Screen::hide() {

}

void Screen::pause() {
    isPaused = true;
}

void Screen::resume() {
    isPaused = false;
}

void Screen::show() {

}

void Screen::updateImpl(float dt) {
    entityManager->update(dt);
}

void Screen::drawImpl() {
    entityManager->draw();
}

void Screen::postDraw() {
    uiRenderer->drawBatches();
}

} // Origin
