#include <iostream>

#include "huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto encoder = HuffmanEncoder();
    char buf[11] = "cccbbdddda";

    encoder.encode(buf, 10);
    encoder.display_encoding();

    return EXIT_SUCCESS;
}
