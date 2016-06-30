#pragma once
#include "Singleton.h"
#include "../Graphics/Camera.h"
#include <list>
#include <glm/glm.hpp>
#include <SDL.h>

using namespace glm;

class Game : public Singleton<Game> {

public:

    enum State {
        PLAY,
        PAUSE
    };

    Game();
    ~Game();
    void create();
    void load();
    void save();
    State getState() { return state; }
    void setState(State state);

private:
    void cameraMove(float dt);
    void update(float dt);
    void keyPress(const SDL_KeyboardEvent& event);
    void mouseButtonAction(const SDL_MouseButtonEvent& event);
    void toggleFullScreen();
    void saveScreenshot();

    float yaw = 0;
    float pitch = 0;
    shared_ptr<Camera> camera;
    State state = PLAY;
};
