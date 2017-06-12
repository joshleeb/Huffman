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
        ("help,h", "Show this help")
        ("verbose,v", po::bool_switch(), "Turn on verbose output")
        ("encode,e", po::bool_switch(), "Encode input")
        ("decode,d", po::bool_switch(), "Decode input")
        ("stats,s", po::bool_switch(), "Show hypothetical statistics")
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
