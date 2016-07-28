#pragma once
#include "../Scene2D.h"
#include "../UI/Rectangle.h"
#include "../UI/LinearLayout.h"

class PauseScene : public Scene2D {

public:
    PauseScene(int width, int height);
    void draw(float dt) override;

private:
    std::shared_ptr<LinearLayout> layout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
    Rectangle continueRect;
    Rectangle exitRect;
};
