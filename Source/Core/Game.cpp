#include "Game.h"
#include "../SceneGraph/Scene.h"
#include "App.h"
#include "../Graphics/Model/Plane.h"

extern App* app;

Game::Game() {

}

void Game::create() {
    shared_ptr<View> playerView = shared_ptr<View>(new View());
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());
    shared_ptr<Plane> plane;
    scene->setRoot(plane);
    playerView->setScene(scene);
    ::app->getViewport()->addView(playerView);
}
