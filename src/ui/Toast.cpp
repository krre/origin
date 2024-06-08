#include "Toast.h"
#include "base/Timer.h"
#include "ui/Label.h"
#include <glm/glm.hpp>

Toast::Toast(Control* parent) : Control(parent) {
    m_timer = new Timer(this);
    m_text = new Label(this);
    m_text->move(5, 0);
    setVisible(false);
    m_timer->timeout.connect(this, &Toast::onTimeout);
}

void Toast::show(const std::string& toastText) {
    m_text->setText(toastText);
    setVisible(true);
    m_timer->start(4000);
}

void Toast::onTimeout() {
    setVisible(false);
}
