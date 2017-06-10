#include <queue>
#include <vector>

#include "heap.h"

using namespace std;

Node::Node(char value, unsigned int score) {
    this->value = value;
    this->score = score;

    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node() {
    if (this->left != nullptr) {
        delete this->left;
    }

    if (this->right != nullptr) {
        delete this->right;
    }
}

bool compare_node_min::operator()(const Node *left, const Node *right) {
    return right->score < left->score;
}

Heap::Heap() {
    priority_queue<Node*, vector<Node*>, compare_node_min> nodes;

    this->nodes = nodes;
}

Heap::~Heap() {
    while (!this->nodes.empty()) {
        delete this->pop();
    }
}

void Heap::push(Node *node) {
    this->nodes.push(node);
}

Node *Heap::pop() {
    Node *root = this->nodes.top();
    this->nodes.pop();

    return root;
}

bool Heap::empty() {
    return this->nodes.empty();
}

int Heap::size() {
    return this->nodes.size();
}
