#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class Options {
    public:
    bool encode, decode, stats, verbose, file_output;
    std::string output;

    Options(bool encode, bool decode, bool stats, bool verbose);
    void set_output(std::string path);
};

Options *process_cli(int argc, char *argv[]);

std::vector<char> read_stdin();

template<typename T>
void display_buf(const std::vector<T> &buf);

inline bool file_exists(const std::string &path);
