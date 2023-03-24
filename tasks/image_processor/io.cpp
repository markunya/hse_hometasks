#include <fstream>
#include "io.h"

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filter_configs) {
    std::vector<std::shared_ptr<Filter>> filters;
    for (const auto& config : filter_configs) {
        if (config.name == AVAILABLE_FILTERS.gray_scale) {
            filters.push_back(std::make_shared<GrayScale>());
        }
        if (config.name == AVAILABLE_FILTERS.negative) {
            filters.push_back(std::make_shared<Negative>());
        }
        if (config.name == AVAILABLE_FILTERS.crop) {
            size_t height = 0;
            size_t width = 0;
            try {
                width = std::stoull(config.arguments[0]);
                height = std::stoull(config.arguments[0]);
            } catch (const std::exception& e) {
                throw InvalidTypeOfArguments();
            }
            filters.push_back(std::make_shared<Crop>(width, height));
        }
    }
    return filters;
}

void FiltersApply(Image& image, std::vector<std::shared_ptr<Filter>> filters) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}