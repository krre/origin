#include "MenuScreen.h"
#include "Scene/Scene.h"
#include "UI/Text/Label.h"
#include "UI/Rectangle.h"

MenuScreen::MenuScreen() {
    menuScene = std::make_shared<Scene>();
    pushScene(menuScene);

    auto rectangle = std::make_shared<Rectangle>(Size(100, 100));
    menuScene->setRootControl(rectangle);
}
