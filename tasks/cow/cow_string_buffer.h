#pragma once

#include <cstddef>

struct CowStringBuffer {
    char* buffer;
    size_t size;
    size_t count;
};