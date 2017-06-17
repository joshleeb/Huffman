#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class options {
    public:
    bool stats, verbose;

    options(bool stats, bool verbose);
    void set_output(std::string path);
};

options* process_cli(int argc, char* argv[]);

std::vector<char> read_stdin();
void write_stdout(std::vector<int> buf);
