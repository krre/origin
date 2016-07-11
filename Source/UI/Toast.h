#pragma once
#include "../Core/Singleton.h"
#include "Text.h"
#include <SDL_timer.h>

class Toast : public Singleton<Toast> {

public:
    Toast();

    void render(float dt);
    void setVisible(bool visible);
    bool getVisible() const { return visible; }

    void showToast(const std::string& toastText);

private:
    static Uint32 onTimeElaplsed(Uint32 interval, void *param);

    bool visible = false;
    Text text;
    SDL_TimerID timerId;
};
