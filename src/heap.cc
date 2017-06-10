#include <queue>
#include <vector>

#include "heap.h"

using namespace std;

Node::Node(int score, char value) {
    this->score = score;
    this->value = value;
}

bool compare_node_lt::operator()(const Node *left, const Node *right) {
    return left->score < right->score;
}

Heap::Heap() {
    priority_queue<Node*, vector<Node*>, compare_node_lt> nodes;

    this->nodes = nodes;
}

Heap::~Heap() {
    while (!this->nodes.empty()) {
        delete this->pop();
    }
}

Node *Heap::root() {
    return this->nodes.top();
}

void Heap::push(Node *node) {
    this->nodes.push(node);
}

Node *Heap::pop() {
    Node *root = this->root();
    this->nodes.pop();

    return root;
}

bool Heap::empty() {
    return this->nodes.empty();
}
