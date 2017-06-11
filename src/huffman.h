#pragma once

#include <unordered_map>
#include <vector>

#include "huffman.h"
#include "minqueue.h"

class HuffmanEncoder {
    std::unordered_map<char, std::vector<bool>> encoding;

    std::unordered_map<char, int> count_chars(char *buf, unsigned int size);
    void evaluate(MinQueueNode *root, std::vector<bool> encoding);

    public:
    HuffmanEncoder();

    char *encode(char *buf, unsigned int size);
    void display_encoding();
};
