#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include "huffman.h"
#include "interface.h"

using namespace std;
namespace fs = boost::filesystem;

int encode(Options *opts) {
    vector<char> buf = read_stdin();
    auto encoder = HuffmanEncoder();
    auto encoded = encoder.encode(buf);

    // TODO: Refactor this into nicer functions.
    // TODO: Add safety check if outfile already exists.
    if (opts->file_output) {
        ofstream outfile(opts->output);
        for (auto const &bit : encoded) {
            outfile << bit;
        }
        outfile << "\n";
        outfile.close();
    } else {
        display_buf(encoded);
    }

    if (opts->verbose) encoder.display_encoding();
    if (opts->stats) encoder.display_stats();

    delete opts;
    return EXIT_SUCCESS;
}

int decode(Options *opts) {
    (void) opts;
    cout << "Decoding isn't implemented... yet\n\n";

    delete opts;
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

    delete opts;
    return EXIT_FAILURE;
}
