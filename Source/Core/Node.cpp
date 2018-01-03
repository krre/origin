#include "Node.h"
#include <algorithm>

namespace Origin {

Node::Node() {

}

void Node::addChild(const std::shared_ptr<Node>& child) {
    children.push_back(child);
    child->setParent(this);
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

size_t Node::count() const {
    return children.size();
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

Node* Node::getParent() const {
    return parent;
}

} // Origin

