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
        ("encode,e", po::bool_switch(), "Encode input")
        ("decode,d", po::bool_switch(), "Decode input")
        ("output,o", po::value<string>()->multitoken()->value_name("FILE"), "File to output to")
        ("stats,s", po::bool_switch(), "Show hypothetical statistics")
        ("verbose,v", po::bool_switch(), "Turn on verbose output")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }

    if (vm.count("encode") && vm.count("decode")) {
        cout << "Cannot specify both to encode and decode\n\n";
        exit(EXIT_FAILURE);
    }

    return vm;
}
