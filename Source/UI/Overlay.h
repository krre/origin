#pragma once
#include "UI/Control.h"

class DebugHUD;
class Toast;
class Console;
class Dialog;

class Overlay : public Control {

public:
    Overlay(Control* parent = nullptr);
    ~Overlay();

    static Overlay* get();

    DebugHUD* getDebugHUD() const { return debugHUD; }
    Toast* getToast() const { return toast; }
    Console* getConsole() const { return console; }

    void toggleDebugHUD();
    void showConsole();
    void showDialog(Dialog* dialog);
    void closeDialog(Dialog* dialog);
    bool isDialogOpen() const { return dialog != nullptr; }
    void invokeDeffered();

private:
   void resizeImpl(int width, int height) override;
   void centerDialog();
    // Save call deffered funtions, e.g. destroy dialog.
    void addDeferredCall(const std::function<void()>& defferedCall) { deferredCalls.push_back(defferedCall); }

    DebugHUD* debugHUD;
    Toast* toast;
    Console* console;
    Dialog* dialog = nullptr;
    std::vector<std::function<void()>> deferredCalls;
};
