#include <iostream>
#include <unordered_map>
#include <vector>

#include <gsl/gsl>

#include "huffman.h"
#include "interface.h"
#include "minqueue.h"

huffman_encoder::huffman_encoder() {
    this->encoding = std::unordered_map<char, std::vector<int>>();
    this->stats = statistics();
}

std::vector<int> huffman_encoder::encode(std::vector<char> buf) {
    if (buf.empty()) return std::vector<int>();

    auto freq = this->count_chars(buf);

    // Set length of original data for statistics (in bits).
    this->stats.original = buf.size() * 8;

    // Push items onto the queue to be sorted by frequency.
    minqueue* queue = new minqueue();
    for (const auto& [value, score] : freq) {
        queue->push(new minqueue_node(value, score));
    }

    minqueue_node* left;
    minqueue_node* right;

    // Combine nodes to form a heap where the root node will be the only node in the queue.
    while (queue->size() > 1) {
        left = queue->pop();
        right = queue->pop();

        minqueue_node* new_node = new minqueue_node(EMPTY_NODE, left->score + right->score);
        new_node->left = left;
        new_node->right = right;

        queue->push(new_node);
    }

    minqueue_node* root = queue->pop();
    delete queue;

    this->evaluate(root, std::vector<int>());
    std::vector<int> encoded = std::vector<int>();

    delete root;

    for (auto& c : buf) {
        std::vector<int> encoding = this->encoding[c];
        encoded.insert(encoded.end(), encoding.begin(), encoding.end());
    }

    // Set length of encoded data for statistics. Each 0|1 character represents a bit, not a byte.
    this->stats.modified = encoded.size();

    return encoded;
}

void huffman_encoder::display_encoding() {
    std::cout << "\n------- Encoding -------\n";
    for (const auto& [c, bits] : this->encoding) {
        std::cout << c << " -> ";
        for (const auto& bit : bits) {
            std::cout << std::hex << bit;
        }
        std::cout << "\n";
    }
    std::cout << "------------------------\n\n";
}

void huffman_encoder::display_stats() {
    double delta = this->stats.original - this->stats.modified;
    double percentage = 100 * delta / this->stats.original;

    std::cout << "\n------ Statistics ------\n";
    std::cout << "Original size = " << this->stats.original << " bits\n";
    std::cout << "Modified size = " << this->stats.modified << " bits\n";
    std::cout << "Space saved = " << percentage <<  "%\n";
    std::cout << "------------------------\n\n";
}

std::unordered_map<char, int> huffman_encoder::count_chars(std::vector<char> buf) {
    std::unordered_map<char, int> freq = {};

    for (const auto& c : buf) {
        if (freq.find(c) == freq.end()) {
            freq[c] = 0;
        }
        freq[c]++;
    }

    return freq;
}

void huffman_encoder::evaluate(minqueue_node* root, std::vector<int> encoding) {
    if (!root) return;
    if (root->value != EMPTY_NODE) {
        this->encoding[root->value] = encoding;
    }

    std::vector<int> left_encoding = encoding;
    left_encoding.push_back(0);

    std::vector<int> right_encoding = encoding;
    right_encoding.push_back(1);

    this->evaluate(root->left, left_encoding);
    this->evaluate(root->right, right_encoding);
}
