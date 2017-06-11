#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto encoder = HuffmanEncoder();

    string input = "cccbbdddda";
    vector<char> buf = vector<char>(input.begin(), input.end());

    vector<int> encoded = encoder.encode(buf);
    for (auto const &bit : encoded) {
        cout << bit;
    }
    cout << "\n";

    return EXIT_SUCCESS;
}
