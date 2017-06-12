#include <iostream>
#include <vector>

#include "huffman.h"
#include "interface.h"

using namespace std;

int encode(Options *opts) {
    auto encoder = HuffmanEncoder(opts);
    vector<char> buf = read_stdin();

    auto encoded = encoder.encode(buf);
    display_buf(encoded);

    return EXIT_SUCCESS;
}

int decode(Options *opts) {
    (void) opts;
    cout << "Decoding isn't implemented... yet\n\n";
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    auto *opts = process_cli(argc, argv);

    if (opts->encode && opts->decode) {
        cerr << "Error: cannot specify both to encode and decode\n\n";
        exit(EXIT_FAILURE);
    }

    if (opts->encode) return encode(opts);
    if (opts->decode) return decode(opts);

    cerr << "Error: must specify either to encode or decode\n\n";
    return EXIT_FAILURE;
}
