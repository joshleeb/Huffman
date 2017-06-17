#include <queue>
#include <vector>

#include "minqueue.h"

MinQueue::MinQueue() {
    this->nodes = std::priority_queue<
        MinQueueNode*, std::vector<MinQueueNode*>, CompareMinQueueNodes>();
}

MinQueue::~MinQueue() {
    while (!this->nodes.empty()) {
        delete this->pop();
    }
}

void MinQueue::push(MinQueueNode *node) {
    this->nodes.push(node);
}

MinQueueNode *MinQueue::pop() {
    MinQueueNode *root = this->nodes.top();
    this->nodes.pop();

    return root;
}

bool MinQueue::empty() {
    return this->nodes.empty();
}

int MinQueue::size() {
    return this->nodes.size();
}
