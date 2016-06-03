#pragma once
#include "Node.h"

class Scene : public Node {

public:
    Scene();
    void setRoot(shared_ptr<Node> root) { this->root = root; }
    Node* getRoot() const { return root.get(); print(root << root.get()); }

private:
    shared_ptr<Node> root;
};
