#include "Node.h"
#include <algorithm>

Node::Node() {

}

void Node::addChild(const std::shared_ptr<Node>& child) {
    children.push_back(child);
}

void Node::removeChild(const std::shared_ptr<Node>& child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void Node::clearChildren() {
    children.clear();
}

std::shared_ptr<Node> Node::getChild(size_t i) const {
    return children.at(i);
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

Node* Node::getParent() const {
    return parent;
}
