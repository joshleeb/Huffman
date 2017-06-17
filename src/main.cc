#include <iostream>
#include <vector>

#include <gsl/gsl>

#include "huffman.h"
#include "interface.h"

int encode(gsl::not_null<options*> opts) {
    std::vector<char> buf = read_stdin();
    auto encoder = huffman_encoder();
    auto encoded = encoder.encode(buf);

    write_stdout(encoded);

    if (opts->verbose) encoder.display_encoding();
    if (opts->stats) encoder.display_stats();

    delete opts;
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    auto opts = process_cli(argc, argv);
    return encode(opts);
}
