#pragma once
#include <memory>

class Node {

public:
    Node();
    virtual void addChild(std::shared_ptr<Node> child) = 0;
    virtual void removeChild(int id) = 0;
};
