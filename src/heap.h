#pragma once

#include <queue>
#include <vector>

class Node {
    public:
    Node(char value, unsigned int score);
    ~Node();

    unsigned int score;
    char value;

    Node *left, *right;
};

struct compare_node_min {
    bool operator()(const Node *left, const Node *right);
};

class Heap {
    std::priority_queue<Node*, std::vector<Node*>, compare_node_min> nodes;

    public:
    Heap();
    ~Heap();

    void push(Node *node);
    Node *pop();

    bool empty();
    int size();
};
