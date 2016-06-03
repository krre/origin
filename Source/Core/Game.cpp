#include "Game.h"
#include "../SceneGraph/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"

extern App* app;

Game::Game() {

}

void Game::addView(shared_ptr<View> view) {
    views.push_back(view);
}

void Game::removeView(shared_ptr<View> view) {
    views.remove(view);
}

void Game::create() {
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    shared_ptr<Plane> plane;
    scene->setRoot(plane);
    ::app->getViewport()->setScene(scene);
}
