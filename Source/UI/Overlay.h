#pragma once
#include "UI/Control.h"

namespace Origin {

class DebugHUD;
class Toast;
class Console;

class Overlay : public Control {

public:
    Overlay(Control* parent = nullptr);
    ~Overlay();
    DebugHUD* getDebugHUD() const { return debugHUD; }
    Toast* getToast() const { return toast; }

    void toggleDebugHUD();
    void toggleConsole();

private:
    DebugHUD* debugHUD;
    Toast* toast;
    Console* console;
};

} // Origin
