#include "parser.h"

ParserOutput Parser(int argc, char** argv) {
    if (argc < 3) {
        throw ArgcMustBeAtLeastThree();
    }
    ParserOutput output;
    output.input_path = argv[1];
    output.output_path = argv[2];
    FilterConfig filter_config;
    int i = 3;
    while (i < argc) {
        filter_config.name = std::string(argv[i]).substr(1);
        filter_config.arguments.clear();
        ++i;
        while (i < argc && argv[i][0] != '-') {
            filter_config.arguments.emplace_back(argv[i]);
            ++i;
        }
        output.filters.emplace_back(filter_config);
    }
    return output;
}