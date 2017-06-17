#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include <gsl/gsl>

#include "huffman.h"
#include "interface.h"

namespace fs = boost::filesystem;

int encode(gsl::not_null<Options *>opts) {
    if (opts->file_output && fs::exists(opts->output)) {
        std::cout << "File already exists. Overwrite? [y/N] ";
        char confirmation = getchar();

        if (tolower(confirmation) != 'y') {
            return EXIT_SUCCESS;
        }
    }

    std::vector<char> buf = read_stdin();
    auto encoder = HuffmanEncoder();
    auto encoded = encoder.encode(buf);

    if (opts->file_output) {
        std::ofstream outfile(opts->output);
        write_buf(encoded, outfile);
        outfile.close();
    } else {
        write_buf(encoded, std::cout);
    }

    if (opts->verbose) encoder.display_encoding();
    if (opts->stats) encoder.display_stats();

    delete opts;
    return EXIT_SUCCESS;
}

int decode(Options *opts) {
    (void) opts;
    std::cout << "Decoding isn't implemented... yet\n\n";

    delete opts;
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    auto *opts = process_cli(argc, argv);

    if (opts->encode && opts->decode) {
        std::cerr << "Error: cannot specify both to encode and decode\n\n";
        exit(EXIT_FAILURE);
    }

    if (opts->encode) return encode(opts);
    if (opts->decode) return decode(opts);

    std::cerr << "Error: must specify either to encode or decode\n\n";

    delete opts;
    return EXIT_FAILURE;
}
