#pragma once

#include <queue>
#include <vector>

class Node {
    public:
    Node(int score, char value);

    int score;
    char value;
};

struct compare_node_lt {
    bool operator()(const Node *left, const Node *right);
};

class Heap {
    std::priority_queue<Node*, std::vector<Node*>, compare_node_lt> nodes;

    public:
    Heap();
    ~Heap();

    Node *root();

    void push(Node *node);
    Node *pop();

    bool empty();
};
