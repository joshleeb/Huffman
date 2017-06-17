#pragma once

#include <unordered_map>
#include <vector>

#include <gsl/gsl>

#include "huffman.h"
#include "interface.h"
#include "minqueue.h"

class statistics {
    public:
    size_t original;
    size_t modified;
};

// TODO Inherit from Huffman class.
class huffman_encoder {
    // Statistics of the current encoding.
    statistics* stats;

    std::unordered_map<char, std::vector<int>> encoding;
    std::unordered_map<char, int> count_chars(std::vector<char> buf);

    void evaluate(minqueue_node* root, std::vector<int> encoding);
    std::vector<int> construct_header(gsl::not_null<minqueue_node*> root);

    public:
    huffman_encoder();
    ~huffman_encoder();

    std::vector<int> encode(std::vector<char> buf);

    void display_encoding();
    void display_stats();
};
