#include "Game.h"
#include "../Scene/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"
#include "../Event/Event.h"
#include "../Event/Input.h"
#include <SDL_keycode.h>

extern App* app;
extern Event* event;
extern Input* input;

Game::Game() {

}

void Game::create() {
    shared_ptr<Plane> plane = shared_ptr<Plane>(new Plane(100, 100));
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    scene->setRoot(plane);
    shared_ptr<View> playerView = shared_ptr<View>(new View());
    playerView->setScene(scene);
    ::app->getViewport()->addView(playerView);
    ::event->update.connectMember(&Game::update, this, std::placeholders::_1);
}

void Game::cameraMove(float dt) {
//    print(dt);
    if (::input->isKeyPressed(SDLK_w)) {
        print("forward")
    } else if (::input->isKeyPressed(SDLK_s)) {
        print("back");
    } else if (::input->isKeyPressed(SDLK_a)) {
        print("left");
    } else if (::input->isKeyPressed(SDLK_d)) {
        print("right");
    }
}

void Game::update(float dt) {
    cameraMove(dt);
}
