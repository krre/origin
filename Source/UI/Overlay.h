#pragma once
#include "UI/Control.h"

namespace Origin {

class DebugHUD;
class Toast;
class Console;
class Dialog;

class Overlay : public Control {

public:
    Overlay(Control* parent = nullptr);
    ~Overlay();
    DebugHUD* getDebugHUD() const { return debugHUD; }
    Toast* getToast() const { return toast; }
    Console* getConsole() const { return console; }

    void toggleDebugHUD();
    void showConsole();
    void showDialog(Dialog* dialog);
    void closeDialog(Dialog* dialog);

private:
   void resizeImpl(int width, int height) override;
   void centerDialog();
    DebugHUD* debugHUD;
    Toast* toast;
    Console* console;
    Dialog* dialog = nullptr;
};

} // Origin
