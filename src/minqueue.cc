#include <queue>
#include <vector>

#include "minqueue.h"

using namespace std;

MinQueue::MinQueue() {
    this->nodes = priority_queue<MinQueueNode*, vector<MinQueueNode*>, CompareMinQueueNodes>();
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
