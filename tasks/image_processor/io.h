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
} const AVAILABLE_FILTERS;

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filter_configs);

void FiltersApply(Image& image, std::vector<std::shared_ptr<Filter>> filters);
