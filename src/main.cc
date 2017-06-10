#include <iostream>

#include "huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
    char buf[11] = "cccbbdddda";
    encode(buf, 10);

    return EXIT_SUCCESS;
}
