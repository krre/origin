#include "Toast.h"
#include "Base/Timer.h"
#include "UI/Label.h"
#include <glm/glm.hpp>

Toast::Toast(Control* parent) : Control(parent) {
    timer = new Timer(this);
    text = new Label(this);
    text->move(5, 0);
    setVisible(false);
    timer->timeout.connect(this, &Toast::onTimeout);
}

Toast::~Toast() {

}

void Toast::show(const std::string& toastText) {
    text->setText(toastText);
    setVisible(true);
    timer->start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}
