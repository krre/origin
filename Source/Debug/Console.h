#pragma once
#include "Scene/Scene2D.h"
#include <SDL.h>

class Label;

class Console : public Scene2D {

public:
    Console();
    void update(float dt) override;

private:
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onWindowResize(int width, int height);
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void execute();
    std::shared_ptr<Label> cmdLine;
};
