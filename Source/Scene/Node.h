#pragma once
#include "../Core/Object.h"
#include <list>

class Node : public Object {

public:
    Node();
    void addChild(shared_ptr<Node> child);
    void removeChild(shared_ptr<Node> child);
    void removeChildren() { nodes.clear(); }
    virtual void draw() {}

private:
    list<shared_ptr<Node>> nodes;
};
