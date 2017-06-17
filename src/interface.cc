#include <iostream>

#include "interface.h"

namespace po = boost::program_options;
using namespace std;

const char *desc_text =
    "huffman [OPTIONS...]\n"
    "Huffman encoder/decoder concept project.\n\n"
    "OPTIONS";

Options *process_cli(int argc, char *argv[]) {
    po::variables_map vm;
    po::options_description desc(desc_text);

    desc.add_options()
        ("help,h", po::bool_switch()->default_value(false), "Show this help")
        ("encode,e", po::bool_switch()->default_value(false), "Encode input")
        ("decode,d", po::bool_switch()->default_value(false), "Decode input")
        ("output,o", po::value<string>()->multitoken()->value_name("FILE"), "File to output to")
        ("stats,s", po::bool_switch()->default_value(false), "Show hypothetical statistics")
        ("verbose,v", po::bool_switch()->default_value(false), "Turn on verbose output")
    ;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n\n";
        exit(EXIT_FAILURE);
    }

    if (vm["help"].as<bool>()) {
        cout << desc << "\n";
        exit(EXIT_SUCCESS);
    }

    Options *opts = new Options(
        vm["encode"].as<bool>(),
        vm["decode"].as<bool>(),
        vm["stats"].as<bool>(),
        vm["verbose"].as<bool>()
    );

    if (vm.count("output")) {
        opts->set_output(vm["output"].as<string>());
    }

    return opts;
}

vector<char> read_stdin() {
    auto buf = vector<char>();
    string line;

    getline(cin, line);
    copy(line.begin(), line.end(), back_inserter(buf));

    while (getline(cin, line)) {
        buf.push_back('\n');
        copy(line.begin(), line.end(), back_inserter(buf));
    }

    return buf;
}

template void write_buf<char>(const vector<char>&, ostream &stream);
template void write_buf<int>(const vector<int>&, ostream &stream);
template<typename T>
void write_buf(const vector<T> &buf, ostream &stream) {
    for (auto const &i : buf) {
        stream << i;
    }
    stream << "\n";
}

Options::Options(bool encode, bool decode, bool stats, bool verbose) {
    this->encode = encode;
    this->decode = decode;
    this->stats = stats;
    this->verbose = verbose;

    this->file_output = false;
}

void Options::set_output(string path) {
    this->file_output = true;
    this->output = path;
}
