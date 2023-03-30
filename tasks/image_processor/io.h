#pragma once

#include <memory>
#include "image.h"
#include "filter.h"
#include "parser.h"
#include "filters/negative.h"
#include "filters/crop.h"
#include "filters/gray_scale.h"

class InvalidTypeOfArguments : public std::exception {};

struct {
    const std::string negative = "neg";
    const std::string crop = "crop";
    const std::string gray_scale = "gs";
    const std::string sharpening = "sharp";
    const std::string edge_detection = "edge";
    const std::string gaussian_blur = "blur";
    const std::string cartoon = "cart";
} const AVAILABLE_FILTERS;

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filter_configs);

void FiltersApply(Image& image, std::vector<std::shared_ptr<Filter>> filters);
