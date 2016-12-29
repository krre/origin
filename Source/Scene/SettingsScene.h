#pragma once
#include "Scene2D.h"
#include "../UI/Button.h"
#include "../UI/LinearLayout.h"

class SettingsScene : public Scene2D {

public:
    SettingsScene();
    ~SettingsScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
};
