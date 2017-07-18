#pragma once
#include "Object.h"
#include <vector>

class Node : public Object {

public:
    Node();
    void addChild(const std::shared_ptr<Node>& child);
    void removeChild(const std::shared_ptr<Node>& child);
    void clearChildren();
    std::shared_ptr<Node> getChild(size_t i) const;
    size_t count() const;

    void setParent(Node* parent);
    Node* getParent() const;

private:
    std::vector<std::shared_ptr<Node>> children;
    Node* parent = nullptr;
};
