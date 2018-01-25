#pragma once
#include <SDL.h>
#include <memory>

namespace Origin {

class Label;

class Console {

public:
    Console();
    void update(float dt);

private:
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
//    void onWindowResize(int width, int height) override;
//    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void execute();
    std::shared_ptr<Label> cmdLine;
};

} // Origin
