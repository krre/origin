#pragma once
#include "Node.h"

class Scene : public Node {

public:
    Scene();

private:
    Node* root;
};
