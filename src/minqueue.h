#pragma once

#include <queue>
#include <vector>

#include <gsl/gsl>

#define EMPTY_NODE '\0'

class minqueue_node {
    public:
    minqueue_node(char value, unsigned int score);
    ~minqueue_node();

    unsigned int score;
    char value;

    minqueue_node* left;
    minqueue_node* right;
};

struct cmp_minqueue_nodes {
    bool operator()(
        const gsl::not_null<minqueue_node*> left, const gsl::not_null<minqueue_node*> right);
};

class minqueue {
    std::priority_queue<
        minqueue_node*, std::vector<minqueue_node*>, cmp_minqueue_nodes> nodes;

    public:
    minqueue();
    ~minqueue();

    void push(gsl::not_null<minqueue_node*> node);
    minqueue_node* pop();

    bool empty();
    int size();
};
