#include "GameScreen.h"
#include "UI/LinearLayout.h"
#include "UI/View3D.h"

namespace Origin {

GameScreen::GameScreen() {
    View3D* mainView = new View3D();
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical);
    layout->addControl(mainView);
    setLayout(layout);
}

} // Origin
