#include "MenuScreen.h"
#include "Scene/Scene.h"
#include "UI/Text/Label.h"

MenuScreen::MenuScreen() {
    menuScene = std::make_shared<Scene>();
    pushScene(menuScene);

    auto label = std::make_shared<Label>();
    label->setText("Label");
    menuScene->setRootControl(label);
}
