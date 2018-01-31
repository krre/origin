#include "MenuScreen.h"
#include "UI/Rectangle.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

MenuScreen::MenuScreen() {
    Rectangle* rectangle = new Rectangle(Size(100, 100), this);
}

} // Origin
