#include "Node.h"

Node::Node() {

}

void Node::addChild(const std::shared_ptr<Node>& child) {
    children.push_back(child);
}
