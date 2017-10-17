#pragma once
#include "Scene/Scene2D.h"
#include <SDL.h>

class Label;

class Console : public Scene2D {

public:
    Console();
    void update(float dt);

private:
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onWindowResize(int width, int height) override;
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void execute();
    std::shared_ptr<Label> cmdLine;
};
