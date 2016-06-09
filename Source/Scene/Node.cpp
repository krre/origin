#include "Node.h"

Node::Node() {

}

void Node::addChild(shared_ptr<Node> child) {
    nodes.push_back(child);
}

void Node::removeChild(shared_ptr<Node> child) {
    nodes.remove(child);
}

void Node::setPosition(float x, float y, float z) {

}

void Node::setRotation(float angle) {

}

void Node::setScale(float scale) {

}
