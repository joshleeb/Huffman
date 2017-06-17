#include <queue>
#include <vector>

#include <gsl/gsl>

#include "minqueue.h"

minqueue::minqueue() {
    this->nodes = std::priority_queue<
        minqueue_node*, std::vector<minqueue_node*>, cmp_minqueue_nodes>();
}

minqueue::~minqueue() {
    while (!this->nodes.empty()) {
        delete this->pop();
    }
}

void minqueue::push(gsl::not_null<minqueue_node*> node) {
    this->nodes.push(node);
}

minqueue_node* minqueue::pop() {
    minqueue_node* root = this->nodes.top();
    this->nodes.pop();

    return root;
}

bool minqueue::empty() {
    return this->nodes.empty();
}

int minqueue::size() {
    return this->nodes.size();
}
