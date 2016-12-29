#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"

class PauseScene : public Scene2D {

public:
    PauseScene();
    ~PauseScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;

private:
    void onContinueButtonClicked();
    void onExitButtonClicked();
    void onKeyPressed(const SDL_KeyboardEvent& event) override;

    std::shared_ptr<LinearLayout> layout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
    Button continueButton;
    Button exitButton;
};
