#include "parser.h"
#include "io.h"
#include "image.h"

int main(int argc, char** argv) {
    ParserOutput parser_output = Parser(argc, argv);
    Image img(parser_output.input_path);
    FiltersApply(img, CreateFilters(parser_output.filters));
    img.Export(parser_output.output_path);
}
