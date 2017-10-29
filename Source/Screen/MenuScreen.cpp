#include "MenuScreen.h"
#include "Scene/Scene.h"
#include "UI/View2D.h"
#include "UI/Text/Label.h"
#include "UI/Rectangle.h"

MenuScreen::MenuScreen(const Size& size) : Screen(size) {
    menuView = std::make_shared<View2D>();
    pushView(menuView);

    auto rectangle = std::make_shared<Rectangle>(Size(100, 100));
    menuView->getScene()->setRootControl(rectangle);
}
