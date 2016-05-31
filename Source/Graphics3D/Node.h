#pragma once
#include "../Core/Object.h"
#include <memory>
#include <list>

class Node : public Object {

public:
    Node();
    virtual void addChild(std::shared_ptr<Node> child) = 0;
    virtual void removeChild(int id) = 0;

private:
    std::list<std::shared_ptr<Node>> nodes;
};
