#include "Node.h"

Node::Node() {

}

void Node::addChild(shared_ptr<Node> child) {
    nodes.push_back(child);
}
