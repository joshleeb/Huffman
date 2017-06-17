#include <iostream>
#include <unordered_map>
#include <vector>

#include <gsl/gsl>

#include "huffman.h"
#include "interface.h"
#include "minqueue.h"

huffman_encoder::huffman_encoder() {
    this->encoding = std::unordered_map<char, std::vector<int>>();
    this->stats = new statistics();
}

huffman_encoder::~huffman_encoder() {
    delete this->stats;
}

std::vector<int> huffman_encoder::encode(std::vector<char> buf) {
    if (buf.empty()) return std::vector<int>();

    auto freq = this->count_chars(buf);

    // Set length of original data for statistics (in bits).
    this->stats->original = buf.size() * 8;

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
    auto header = this->construct_header(root);
    uint16_t header_size = header.size();
    std::vector<int> encoded = this->construct_header(root);

    delete root;

    // Insert 'H<HEADER_SIZE>' into the header. Note that <HEADER_SIZE> is a 16 bit unsigned int that
    // represents the number of bits in the header after `H<HEADER_SIZE>`.
    for (int bit_index = 0; bit_index < 16; bit_index++) {
        encoded.insert(encoded.begin(), header_size >> bit_index & 1);
    }
    for (int bit_index = 0; bit_index < 7; bit_index++) {
        encoded.insert(encoded.begin(), 'H' >> bit_index & 1);
    }

    for (auto& c : buf) {
        std::vector<int> encoding = this->encoding[c];
        encoded.insert(encoded.end(), encoding.begin(), encoding.end());
    }

    // Set length of encoded data for statistics. Each 0|1 character represents a bit, not a byte.
    this->stats->modified = encoded.size();

    return encoded;
}

// TODO: Handle escape characters.
void huffman_encoder::display_encoding() {
    std::cout << "\n------- Encoding -------\n";
    for (const auto& [c, bits] : this->encoding) {
        std::cout << c << " -> ";
        for (const auto& bit : bits) {
            std::cout << bit;
        }
        std::cout << "\n";
    }
    std::cout << "------------------------\n\n";
}

void huffman_encoder::display_stats() {
    double delta = this->stats->original - this->stats->modified;
    double percentage = 100 * delta / this->stats->original;

    std::cout << "\n------ Statistics ------\n";
    std::cout << "Original size = " << this->stats->original << " bits\n";
    std::cout << "Modified size = " << this->stats->modified << " bits\n";
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

// Construct the header for the current encoding. The header is a simple representation of the
// structure of the binary tree. A `0` denotes moving along the tree, and a `1` denotes that the next
// sequence of 7 bits is a character.
std::vector<int> huffman_encoder::construct_header(gsl::not_null<minqueue_node*> root) {
    auto header = std::vector<int>();
    std::vector<int> sub_header;

    if (!root->left && !root->right) {
        header.push_back(1);
        for (int bit_index = 6; bit_index >= 0; bit_index--) {
            header.push_back(root->value >> bit_index & 1);
        }
    } else {
        header.push_back(0);
    }

    if (root->left) {
        sub_header = this->construct_header(root->left);
        header.insert(header.end(), sub_header.begin(), sub_header.end());
    }

    if (root->right) {
        sub_header = this->construct_header(root->right);
        header.insert(header.end(), sub_header.begin(), sub_header.end());
    }

    return header;
}
