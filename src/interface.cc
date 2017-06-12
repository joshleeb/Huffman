#include <iostream>

#include "interface.h"

namespace po = boost::program_options;
using namespace std;

const char *desc_text =
    "huffman [OPTIONS...]\n"
    "Huffman encoder/decoder concept project.\n\n"
    "OPTIONS";

po::variables_map process_cli(int argc, char *argv[]) {
    po::options_description desc(desc_text);
    desc.add_options()
        ("help", "Show this help")
        ("verbose", po::bool_switch(), "Turn on verbose output")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }

    return vm;
}
