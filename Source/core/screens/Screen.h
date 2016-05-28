#pragma once
#include "../Node.h"

class Screen {

public:
    Screen() {}
    virtual void update() {}
    virtual void render() = 0;
private:
    Node* rootNode;
};
