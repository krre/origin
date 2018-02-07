#include "Screen.h"
#include "UI/Control.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "ECS/EntityManager.h"
#include "Core/Game.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
    renderPassResources.push_back(Game::getUIRenderer()->getRenderPassUI());
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
    Game::getEntityManager()->update(dt);
}

void Screen::drawImpl() {
    Game::getEntityManager()->draw();
}

void Screen::postDraw() {
    Game::getUIRenderer()->drawBatches();
}

} // Origin
