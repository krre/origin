#pragma once
#include "ui/Control.h"

class DebugHUD;
class Toast;
class Console;
class Dialog;

class Overlay : public Control {
public:
    Overlay(Control* parent = nullptr);
    ~Overlay();

    static Overlay* get();

    DebugHUD* debugHUD() const { return m_debugHUD; }
    Toast* toast() const { return m_toast; }
    Console* console() const { return m_console; }

    void toggleDebugHUD();
    void showConsole();
    void showDialog(Dialog* dialog);
    void closeDialog(Dialog* dialog);
    bool isDialogOpen() const { return m_dialog != nullptr; }
    void invokeDeffered();

private:
   void resizeImpl(int width, int height) override;
   void centerDialog();
    // Save call deffered funtions, e.g. destroy dialog.
    void addDeferredCall(const std::function<void()>& defferedCall) { m_deferredCalls.push_back(defferedCall); }

    DebugHUD* m_debugHUD = nullptr;
    Toast* m_toast = nullptr;
    Console* m_console = nullptr;
    Dialog* m_dialog = nullptr;
    std::vector<std::function<void()>> m_deferredCalls;
};
