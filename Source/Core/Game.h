#pragma once
#include "Singleton.h"
#include "../Graphics/Camera.h"
#include <list>
#include <glm/glm.hpp>
#include <SDL.h>

class Game : public Singleton<Game> {

public:

    enum State {
        PLAY,
        PAUSE,
        CONSOLE
    };

    Game();
    void create();
    void load();
    void save();

    State getState() { return state; }
    void setState(State state);

    bool getWireframe() const { return wireframe; }

    void cameraMove(float dt);

private:
    void keyPress(const SDL_KeyboardEvent& event);
    void mouseButtonAction(const SDL_MouseButtonEvent& event);
    void toggleFullScreen();
    void saveScreenshot();

    float yaw = 0;
    float pitch = 0;
    std::shared_ptr<Camera> camera;
    State state = PLAY;
    bool wireframe = false; // TODO: Move to renderer
};
