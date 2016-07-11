#pragma once
#include "Node.h"

class Scene : public Node {

public:
    Scene();
    void setRoot(std::shared_ptr<Node> root) { this->root = root; }
    Node* getRoot() const { return root.get(); }

private:
    std::shared_ptr<Node> root;
};
