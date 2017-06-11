#include <iostream>
#include <vector>

#include <gflags/gflags.h>

#include "huffman.h"

using namespace std;

DEFINE_bool(verbose, false, "Show mapping from char to bits for encoder/decoder");

int main(int argc, char *argv[]) {
    auto encoder = HuffmanEncoder();

    gflags::SetUsageMessage("Huffman usage:");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    string input = "cccbbdddda";
    vector<char> buf = vector<char>(input.begin(), input.end());

    vector<int> encoded = encoder.encode(buf);
    for (auto const &bit : encoded) {
        cout << bit;
    }
    cout << "\n";

    return EXIT_SUCCESS;
}
