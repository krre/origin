#pragma once
#include "Scene/Scene2D.h"
#include "UI/Button.h"
#include "UI/UITypes.h"

class LinearLayout;

class PauseScene : public Scene2D {

public:
    PauseScene();
    ~PauseScene();
    void init() override;
    void update(float dt) override;

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void onContinueButtonClicked();
    void onExitButtonClicked();

    std::shared_ptr<LinearLayout> layout = std::make_shared<LinearLayout>(Direction::VERICAL);
    Button continueButton;
    Button exitButton;
};
