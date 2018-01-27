#include "GameScreen.h"
#include "UI/LinearLayout.h"
#include "UI/Rectangle.h"

namespace Origin {

GameScreen::GameScreen() {
    Rectangle* rectangle = new Rectangle(Size(100, 100));
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical);
    layout->addControl(rectangle);
    setLayout(layout);
}

} // Origin
