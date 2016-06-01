#pragma once
#include "../Core/Object.h"
#include <list>

class Node : public Object {

public:
    Node();
    virtual void addChild(shared_ptr<Node> child) = 0;
    virtual void removeChild(int id) = 0;

private:
    list<shared_ptr<Node>> nodes;
};
