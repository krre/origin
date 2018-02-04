#include "MenuScreen.h"
#include "UI/Rectangle.h"
#include "UI/Label.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

MenuScreen::MenuScreen() {
    Rectangle* rectangle1 = new Rectangle(Size(500, 500), this);
    rectangle1->setPosition(Pos2(50, 50));
    rectangle1->setColor(Color(0.0, 1.0, 0.0));

    Rectangle* rectangle2 = new Rectangle(Size(200, 200), rectangle1);
    rectangle2->setPosition(Pos2(20, 20));
    rectangle2->setColor(Color(1.0, 0.0, 0.0));

    Label* label = new Label("origin", rectangle2);
    label->setPosition(Pos2(15, 15));
    label->setColor(Color(0.4, 0.7, 1.0));
}

} // Origin
