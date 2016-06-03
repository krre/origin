#pragma once
#include "Node.h"

class Scene : public Node {

public:
    Scene();
    void setRoot(shared_ptr<Node> root) { this->root = root; }

private:
    shared_ptr<Node> root;
};
