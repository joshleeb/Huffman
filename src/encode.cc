#include <iostream>
#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "minqueue.h"

using namespace std;

HuffmanEncoder::HuffmanEncoder() {
    this->encoding = unordered_map<char, vector<bool>>();
}

char *HuffmanEncoder::encode(char *buf, unsigned int size) {
    auto freq = this->count_chars(buf, size);

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

    this->evaluate(root, vector<bool>());
    delete root;

    return buf;
}

void HuffmanEncoder::display_encoding() {
    for (auto const &i : this->encoding) {
        cout << i.first << " -> ";
        for (auto const &bit : i.second) {
            cout << (int) bit;
        }
        cout << "\n";
    }
}

unordered_map<char, int> HuffmanEncoder::count_chars(char *buf, unsigned int size) {
    unordered_map<char, int> freq = {};

    for (unsigned int i = 0; i < size; i++) {
        if (freq.find(buf[i]) == freq.end()) {
            freq[buf[i]] = 0;
        }
        freq[buf[i]]++;
    }

    return freq;
}

void HuffmanEncoder::evaluate(MinQueueNode *root, vector<bool> encoding) {
    if (!root) return;
    if (root->value != EMPTY_NODE) {
        this->encoding[root->value] = encoding;
    }

    vector<bool> left_encoding = encoding;
    left_encoding.push_back(0);

    vector<bool> right_encoding = encoding;
    right_encoding.push_back(1);

    this->evaluate(root->left, left_encoding);
    this->evaluate(root->right, right_encoding);
}
