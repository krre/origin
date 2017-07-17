#pragma once
#include "Object.h"
#include <vector>

class Node : public Object {

public:
    Node();
    void addChild(const std::shared_ptr<Node>& child);

private:
    std::vector<std::shared_ptr<Node>> children;
};
