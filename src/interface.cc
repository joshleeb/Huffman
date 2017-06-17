#include <iostream>

#include "interface.h"

namespace po = boost::program_options;

const char* desc_text =
    "huffman [OPTIONS...]\n"
    "Huffman encoder concept project.\n\n"
    "OPTIONS";

options* process_cli(int argc, char* argv[]) {
    po::variables_map vm;
    po::options_description desc(desc_text);

    desc.add_options()
        ("help,h", po::bool_switch()->default_value(false), "Show this help")
        ("stats,s", po::bool_switch()->default_value(false), "Show hypothetical statistics")
        ("verbose,v", po::bool_switch()->default_value(false), "Turn on verbose output")
    ;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
        exit(EXIT_FAILURE);
    }

    if (vm["help"].as<bool>()) {
        std::cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }

    options* opts = new options(
        vm["stats"].as<bool>(),
        vm["verbose"].as<bool>()
    );

    return opts;
}

std::vector<char> read_stdin() {
    auto buf = std::vector<char>();
    std::string line;

    do {
        copy(line.begin(), line.end(), back_inserter(buf));
        buf.push_back('\n');
    } while (getline(std::cin, line));

    return buf;
}

void write_stdout(std::vector<int> buf) {
    for (const auto& c : buf) {
        std::cout << c;
    }
    std::cout << "\n";
}

options::options(bool stats, bool verbose) {
    this->stats = stats;
    this->verbose = verbose;
}
