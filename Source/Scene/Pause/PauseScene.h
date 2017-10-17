#pragma once
#include "Scene/Scene2D.h"

class LinearLayout;
class Button;

class PauseScene : public Scene2D {

public:
    PauseScene();
    ~PauseScene();
    void init() override;
    void update(float dt);

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void onContinueButtonClicked();
    void onExitButtonClicked();

    std::shared_ptr<LinearLayout> layout;
    std::unique_ptr<Button> continueButton;
    std::unique_ptr<Button> exitButton;
};
