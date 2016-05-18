#pragma once

class Screen {

public:
    Screen() {}
    virtual void update() {}
    virtual void render() = 0;
};
