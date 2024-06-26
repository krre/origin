#pragma once
#include <core/SingleObject.h>

struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseButtonEvent;

class UIManager : public Core::SingleObject<UIManager> {
public:
    UIManager(Object* parent = nullptr);

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onTextInput(const SDL_TextInputEvent& event);
    void onMouseButtonAction(const SDL_MouseButtonEvent& event);
    void traverseOverLeaf(Object* object, const SDL_MouseButtonEvent& event);
};
