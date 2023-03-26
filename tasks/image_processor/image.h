#pragma once

#include <vector>
#include <string>
#include "rgb.h"

class Image {
public:
    class CouldNotOpenFile : public std::exception {};

    explicit Image(const std::string& in_path);
    void Export(const std::string& out_path);

    uint32_t Width() const;
    uint32_t Height() const;

    std::vector<RGB>& operator[](uint32_t i);
    bool operator==(const Image& other) const;
    void ReplaceImage(const std::vector<std::vector<RGB>>& other_image);
    void Resize(size_t new_width, size_t new_height);

private:
    std::vector<std::vector<RGB>> image_;
    uint32_t width_;
    uint32_t height_;

    const uint8_t file_header_size_ = 14;
    const uint8_t info_header_size_ = 40;
};