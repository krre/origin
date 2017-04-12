#pragma once
#include "../Scene/Scene2D.h"
#include "../UI/Text/Label.h"
#include <SDL.h>

class Console : public Scene2D {

public:
    Console();
    void draw(float dt) override;
    void update(float dt) override;
    void setVisible(bool visible) override;

private:
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onWindowResize(int width, int height);
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void execute();
    Label cmdLine;
};
