#pragma once

#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "minqueue.h"

class HuffmanEncoder {
    std::unordered_map<char, std::vector<int>> encoding;
    std::unordered_map<char, int> count_chars(std::vector<char> buf);

    void evaluate(MinQueueNode *root, std::vector<int> encoding);

    public:
    HuffmanEncoder();

    std::vector<int> encode(std::vector<char> buf);
    void display_encoding();
};
