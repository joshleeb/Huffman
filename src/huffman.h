#pragma once

#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "interface.h"
#include "minqueue.h"

class HuffmanEncoder {
    // Options mainly used by the CLI. Can be set to NULL if required.
    Options *opts;

    std::unordered_map<char, std::vector<int>> encoding;
    std::unordered_map<char, int> count_chars(std::vector<char> buf);

    void evaluate(MinQueueNode *root, std::vector<int> encoding);

    public:
    HuffmanEncoder(Options *opts);

    std::vector<int> encode(std::vector<char> buf);
    void display_encoding();
};
