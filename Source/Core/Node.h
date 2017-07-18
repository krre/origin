#pragma once
#include "Object.h"
#include <vector>

class Node : public Object {

public:
    Node();
    void addChild(const std::shared_ptr<Node>& child);
    void removeChild(const std::shared_ptr<Node>& child);

    void setParent(Node* parent);
    Node* getParent() const;

private:
    std::vector<std::shared_ptr<Node>> children;
    Node* parent = nullptr;
};
