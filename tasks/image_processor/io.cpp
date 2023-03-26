#include <fstream>
#include "io.h"
#include "filters/sharpening.h"
#include "filters/edge_detection.h"
#include "filters/gausian_blur.h"

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filter_configs) {
    std::vector<std::shared_ptr<Filter>> filters;
    for (const auto& config : filter_configs) {
        if (config.name == AVAILABLE_FILTERS.gray_scale) {
            filters.push_back(std::make_shared<GrayScale>());
            continue;
        }
        if (config.name == AVAILABLE_FILTERS.negative) {
            filters.push_back(std::make_shared<Negative>());
            continue;
        }
        if (config.name == AVAILABLE_FILTERS.crop) {
            size_t height = 0;
            size_t width = 0;
            try {
                width = std::stoull(config.arguments[0]);
                height = std::stoull(config.arguments[1]);
            } catch (const std::exception& e) {
                throw InvalidTypeOfArguments();
            }
            filters.push_back(std::make_shared<Crop>(width, height));
            continue;
        }
        if (config.name == AVAILABLE_FILTERS.sharpening) {
            filters.push_back(std::make_shared<Sharpening>());
            continue;
        }
        if (config.name == AVAILABLE_FILTERS.edge_detection) {
            double threshold = 0;
            try {
                threshold = std::stod(config.arguments[0]);
            } catch (const std::exception& e) {
                throw InvalidTypeOfArguments();
            }
            filters.push_back(std::make_shared<EdgeDetection>(threshold));
            continue;
        }
        if (config.name == AVAILABLE_FILTERS.gaussian_blur) {
            double sigma = 0;
            try {
                sigma = std::stod(config.arguments[0]);
            } catch (const std::exception& e) {
                throw InvalidTypeOfArguments();
            }
            filters.push_back(std::make_shared<GaussianBlur>(sigma));
            continue;
        }
    }
    return filters;
}

void FiltersApply(Image& image, std::vector<std::shared_ptr<Filter>> filters) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}