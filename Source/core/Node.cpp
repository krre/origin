#include "Node.h"

Node::Node() {

}

void Node::addChild(std::shared_ptr<Node> child) {
    nodes.push_back(child);
}
