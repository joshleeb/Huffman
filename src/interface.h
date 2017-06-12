#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

po::variables_map process_cli(int argc, char *argv[]);
