#pragma once
#include "UI/Control.h"
#include <SDL.h>
#include <memory>

namespace Origin {

class Label;

class Console : Control {

public:
    Console();

private:
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
//    void onWindowResize(int width, int height) override;
//    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void execute();
    Label* cmdLine;
};

} // Origin
