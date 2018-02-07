#include "Screen.h"
#include "UI/Control.h"
#include "Core/Context.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"
#include "ECS/EntityManager.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
    renderPassResources.push_back(Context::get()->getUIRenderer()->getRenderPassUI());
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
    Context::get()->getEntityManager()->update(dt);
}

void Screen::drawImpl() {
    Context::get()->getEntityManager()->draw();
}

void Screen::postDraw() {
    Context::get()->getUIRenderer()->drawBatches();
}

} // Origin
