#pragma once

#include <queue>
#include <vector>

#define EMPTY_NODE '\0'

class MinQueueNode {
    public:
    MinQueueNode(char value, unsigned int score);
    ~MinQueueNode();

    unsigned int score;
    char value;

    MinQueueNode *left, *right;
};

struct CompareMinQueueNodes {
    bool operator()(const MinQueueNode *left, const MinQueueNode *right);
};

class MinQueue {
    std::priority_queue<MinQueueNode*, std::vector<MinQueueNode*>, CompareMinQueueNodes> nodes;

    public:
    MinQueue();
    ~MinQueue();

    void push(MinQueueNode *node);
    MinQueueNode *pop();

    bool empty();
    int size();
};
