#include <iostream>
#include <vector>

#include "huffman.h"
#include "interface.h"

using namespace std;

int main(int argc, char *argv[]) {
    auto *opts = process_cli(argc, argv);

    if (opts->encode && opts->decode) {
        cout << "Error: cannot specify both to encode and decode\n\n";
        exit(EXIT_FAILURE);
    } else if (!opts->encode && !opts->decode) {
        cout << "Error: must specify either to encode or decode\n\n";
        exit(EXIT_FAILURE);
    }

    if (opts->encode) {
        cout << "Encoding isn't implemented... yet\n\n";
    } else if (opts->decode) {
        cout << "Decoding isn't implemented... yet\n\n";
    }

    // auto encoder = HuffmanEncoder();
    // string input = "cccbbdddda";
    // vector<char> buf = vector<char>(input.begin(), input.end());

    // vector<int> encoded = encoder.encode(buf);
    // for (auto const &bit : encoded) {
    //     cout << bit;
    // }
    // cout << "\n";

    return EXIT_SUCCESS;
}
