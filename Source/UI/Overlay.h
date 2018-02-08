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
    Console* getConsole() const { return console; }

    void toggleDebugHUD();
    void showConsole();

private:
   void resizeImpl(int width, int height) override;
    DebugHUD* debugHUD;
    Toast* toast;
    Console* console;
};

} // Origin
