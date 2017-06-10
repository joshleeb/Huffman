#include <iostream>
#include <unordered_map>

#include "heap.h"
#include "huffman.h"

using namespace std;

void printCodes(Node* root, string str)
{
    if (!root)
        return;

    if (root->value != '\0')
        cout << root->value << "(" << root->score << ") : " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

char *encode(char *buf, unsigned int size) {
    unordered_map<char, int> freq = {};

    // Count all characters in the buffer.
    for (unsigned int i = 0; i < size; i++) {
        if (freq.find(buf[i]) == freq.end()) {
            freq[buf[i]] = 0;
        }

        freq[buf[i]]++;
    }

    // Push items onto the heap to be sorted by frequency.
    Heap *heap = new Heap();
    for (auto const &k : freq) {
        heap->push(new Node(k.first, k.second));
    }

    Node *left, *right;

    while (heap->size() > 1) {
        left = heap->pop();
        right = heap->pop();

        Node *new_node = new Node('\0', left->score + right->score);

        new_node->left = left;
        new_node->right = right;

        heap->push(new_node);
    }

    Node *root = heap->pop();
    delete heap;

    printCodes(root, "");
    delete root;

    return buf;
}
