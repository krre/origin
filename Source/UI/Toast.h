#pragma once
#include "../Core/Singleton.h"
#include "Text.h"
#include "../Core/Timer.h"

class Toast : public Singleton<Toast> {

public:
    Toast();

    void render(float dt);
    void setVisible(bool visible);
    bool getVisible() const { return visible; }

    void showToast(const std::string& toastText);

private:
    void onTimeout();
    bool visible = false;
    Text text;
    Timer timer;
};
