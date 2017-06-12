#pragma once

#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "interface.h"
#include "minqueue.h"

class Statistics {
    public:
    size_t original;
    size_t modified;
};

class HuffmanEncoder {
    // Statistics of the current encoding.
    Statistics *stats;

    std::unordered_map<char, std::vector<int>> encoding;
    std::unordered_map<char, int> count_chars(std::vector<char> buf);

    void evaluate(MinQueueNode *root, std::vector<int> encoding);

    public:
    HuffmanEncoder();
    ~HuffmanEncoder();

    std::vector<int> encode(std::vector<char> buf);

    void display_encoding();
    void display_stats();
};
