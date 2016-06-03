#include "Game.h"
#include "../SceneGraph/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"

extern App* app;

Game::Game() {

}

void Game::create() {
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    shared_ptr<Plane> plane;
    scene->setRoot(plane);
    ::app->getViewport()->setScene(scene);
    ::app->getViewport()->addView(shared_ptr<PlayerView>(new PlayerView));
}
