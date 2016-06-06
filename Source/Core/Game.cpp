#include "Game.h"
#include "../SceneGraph/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"

extern App* app;

Game::Game() {

}

void Game::create() {
    shared_ptr<Plane> plane = shared_ptr<Plane>(new Plane(100, 100));
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    scene->setRoot(plane);
    shared_ptr<View> playerView = shared_ptr<View>(new View());
    playerView->setScene(scene);
    ::app->getViewport()->addView(playerView);
}
