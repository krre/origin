#include "Node.h"

Node::Node() {

}

void Node::addChild(const std::shared_ptr<Node>& child) {
    children.push_back(child);
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

Node* Node::getParent() const {
    return parent;
}
