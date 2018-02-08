#include "Event.h"
#include "Input.h"
#include "Core/Game.h"

namespace Origin {

Event::Event() {

}

void Event::handleEvents() {
    Game::getInput()->mouseReset();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Game::quit();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    windowResize.fire(event.window.data1, event.window.data2);
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    windowMove.fire(event.window.data1, event.window.data2);
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                Game::getInput()->setMousePos(glm::ivec2(event.motion.x, event.motion.y));
                Game::getInput()->setRelMousePos(glm::ivec2(event.motion.xrel, event.motion.yrel));
                mouseMove.fire(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseButtonAction.fire(event.button);
                break;
            case SDL_MOUSEWHEEL:
                break;
            case SDL_KEYDOWN:
                // Use keyLock to fix bug on some Linux system, when catch two SDL_KEYDOWN event and one SDL_KEYUP
                if (!keyLock) {
                    Game::getInput()->addKey(event.key.keysym.sym);
                    Game::getInput()->isKeyAccepted = false;
                    keyPressed.fire(event.key);
                    keyLock = true;
                }
                break;
            case SDL_KEYUP:
                Game::getInput()->removeKey(event.key.keysym.sym);
                Game::getInput()->isKeyAccepted = false;
                keyRelease.fire(event.key);
                keyLock = false;
                break;
    //        case SDL_TextInputEvent:
    //            break;
    //        case SDL_TextEditingEvent:
    //            break;
            default:
                break;
        }
    }
}

} // Origin
