#include <iostream>
#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "minqueue.h"

using namespace std;

HuffmanEncoder::HuffmanEncoder() {
    this->encoding = unordered_map<char, vector<int>>();
}

vector<int> HuffmanEncoder::encode(vector<char> buf) {
    auto freq = this->count_chars(buf);

    // Push items onto the queue to be sorted by frequency.
    MinQueue *queue = new MinQueue();
    for (auto const &i : freq) {
        queue->push(new MinQueueNode(i.first, i.second));
    }

    // Combine nodes to form a heap where the root node will be the only node in the queue.
    MinQueueNode *left, *right;
    while (queue->size() > 1) {
        left = queue->pop();
        right = queue->pop();

        MinQueueNode *new_node = new MinQueueNode(EMPTY_NODE, left->score + right->score);
        new_node->left = left;
        new_node->right = right;

        queue->push(new_node);
    }

    MinQueueNode *root = queue->pop();
    delete queue;

    this->evaluate(root, vector<int>());
    delete root;

    vector<int> encoded = vector<int>();
    for (auto &c : buf) {
        vector<int> encoding = this->encoding[c];
        encoded.insert(encoded.end(), encoding.begin(), encoding.end());
    }

    return encoded;
}

void HuffmanEncoder::display_encoding() {
    for (auto const &i : this->encoding) {
        cout << i.first << " -> ";
        for (auto const &bit : i.second) {
            cout << bit;
        }
        cout << "\n";
    }
}

unordered_map<char, int> HuffmanEncoder::count_chars(vector<char> buf) {
    unordered_map<char, int> freq = {};

    for (auto &c : buf) {
        if (freq.find(c) == freq.end()) {
            freq[c] = 0;
        }
        freq[c]++;
    }

    return freq;
}

void HuffmanEncoder::evaluate(MinQueueNode *root, vector<int> encoding) {
    if (!root) return;
    if (root->value != EMPTY_NODE) {
        this->encoding[root->value] = encoding;
    }

    vector<int> left_encoding = encoding;
    left_encoding.push_back(0);

    vector<int> right_encoding = encoding;
    right_encoding.push_back(1);

    this->evaluate(root->left, left_encoding);
    this->evaluate(root->right, right_encoding);
}
