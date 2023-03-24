#pragma once

#include <string>
#include <vector>

class ArgcMustBeAtLeastThree : public std::exception {};

struct FilterConfig {
    std::string name;
    std::vector<std::string> arguments;
};

struct ParserOutput {
    std::string input_path;
    std::string output_path;
    std::vector<FilterConfig> filters;
};

ParserOutput Parser(int argc, char** argv);