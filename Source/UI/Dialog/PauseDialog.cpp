#include "PauseDialog.h"
#include "UI/Label.h"

namespace Origin {

PauseDialog::PauseDialog() {
    Label* label = new Label("Pause", this);
    label->setColor(Color::WHITE);
    resizeToContent();
}

} // Origin
