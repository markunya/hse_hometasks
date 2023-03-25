#include "image.h"

#include <fstream>
#include <iostream>

uint32_t Image::Width() const {
    return width_;
};
uint32_t Image::Height() const {
    return height_;
}

std::vector<RGB>& Image::operator[](uint32_t i) {
    return image_[i];
}

void Image::ReplaceImage(const std::vector<std::vector<RGB>>& other_image) {
    image_ = other_image;
}

void Image::Resize(size_t new_width, size_t new_height) {
    width_ = new_width;
    height_ = new_height;
}

Image::Image(const std::string& in_path) {
    std::ifstream f;
    f.open(in_path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        throw CouldNotOpenFile();
    }

    uint8_t file_header[file_header_size_];
    f.read(reinterpret_cast<char*>(file_header), file_header_size_);

    uint8_t info_header[info_header_size_];
    f.read(reinterpret_cast<char*>(info_header), info_header_size_);

    // Magic numbers
    const int shift_1_byte = 8;
    const int shift_2_byte = 16;
    const int shift_3_byte = 24;

    const int non_zero_byte_4 = 4;
    const int non_zero_byte_5 = 5;
    const int non_zero_byte_6 = 6;
    const int non_zero_byte_7 = 7;
    const int non_zero_byte_8 = 8;
    const int non_zero_byte_9 = 9;
    const int non_zero_byte_10 = 10;
    const int non_zero_byte_11 = 11;

    width_ = info_header[non_zero_byte_4] + (info_header[non_zero_byte_5] << shift_1_byte) +
             (info_header[non_zero_byte_6] << shift_2_byte) + (info_header[non_zero_byte_7] << shift_3_byte);

    height_ = info_header[non_zero_byte_8] + (info_header[non_zero_byte_9] << shift_1_byte) +
              (info_header[non_zero_byte_10] << shift_2_byte) + (info_header[non_zero_byte_11] << shift_3_byte);

    std::vector<std::vector<RGB>> pixels(height_, std::vector<RGB>(width_));
    image_ = pixels;
    pixels.clear();

    const uint8_t padding_amount = (4 - (width_ * 3) % 4) % 4;

    const double max_color_value = 255.0;

    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            uint8_t rgb[3];
            f.read(reinterpret_cast<char*>(rgb), 3);

            image_[i][j] =
                RGB(static_cast<double>(rgb[2] / max_color_value), static_cast<double>(rgb[1] / max_color_value),
                    static_cast<double>(rgb[0] / max_color_value));
        }
        f.ignore(padding_amount);
    }

    f.close();
};

void Image::Export(const std::string& out_path) {
    std::ofstream f;
    f.open(out_path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        throw CouldNotOpenFile();
    }

    uint8_t bmp_pad[3] = {0, 0, 0};
    const uint8_t padding_amount = (4 - (width_ * 3) % 4) % 4;

    const uint32_t file_size = static_cast<size_t>(height_) * (static_cast<size_t>(width_) * 3 + padding_amount) +
                               file_header_size_ + info_header_size_;

    // Magic numbers
    const uint8_t shift_1_byte = 8;
    const uint8_t shift_2_byte = 16;
    const uint8_t shift_3_byte = 24;

    const uint8_t non_zero_byte_0 = 0;
    const uint8_t non_zero_byte_1 = 1;
    const uint8_t non_zero_byte_2 = 2;
    const uint8_t non_zero_byte_3 = 3;
    const uint8_t non_zero_byte_4 = 4;
    const uint8_t non_zero_byte_5 = 5;
    const uint8_t non_zero_byte_10 = 10;

    uint8_t file_header[file_header_size_];

    for (int i = 0; i < file_header_size_; ++i) {
        file_header[i] = 0;
    }

    file_header[non_zero_byte_0] = 'B';
    file_header[non_zero_byte_1] = 'M';

    file_header[non_zero_byte_2] = file_size;
    file_header[non_zero_byte_3] = file_size >> shift_1_byte;
    file_header[non_zero_byte_4] = file_size >> shift_2_byte;
    file_header[non_zero_byte_5] = file_size >> shift_3_byte;

    file_header[non_zero_byte_10] = file_header_size_ + info_header_size_;

    uint8_t info_header[info_header_size_];

    for (size_t i = 0; i < info_header_size_; ++i) {
        info_header[i] = 0;
    }

    // Magic numbers
    const uint8_t non_zero_byte_0_info = 0;
    const uint8_t non_zero_byte_4_info = 4;
    const uint8_t non_zero_byte_5_info = 5;
    const uint8_t non_zero_byte_6_info = 6;
    const uint8_t non_zero_byte_7_info = 7;
    const uint8_t non_zero_byte_8_info = 8;
    const uint8_t non_zero_byte_9_info = 9;
    const uint8_t non_zero_byte_10_info = 10;
    const uint8_t non_zero_byte_11_info = 11;
    const uint8_t non_zero_byte_12_info = 12;
    const uint8_t non_zero_byte_14_info = 14;

    const uint8_t bits_per_pixel = 24;

    info_header[non_zero_byte_0_info] = info_header_size_;

    info_header[non_zero_byte_4_info] = width_;
    info_header[non_zero_byte_5_info] = width_ >> shift_1_byte;
    info_header[non_zero_byte_6_info] = width_ >> shift_2_byte;
    info_header[non_zero_byte_7_info] = width_ >> shift_3_byte;

    info_header[non_zero_byte_8_info] = height_;
    info_header[non_zero_byte_9_info] = height_ >> shift_1_byte;
    info_header[non_zero_byte_10_info] = height_ >> shift_2_byte;
    info_header[non_zero_byte_11_info] = height_ >> shift_3_byte;

    info_header[non_zero_byte_12_info] = 1;

    info_header[non_zero_byte_14_info] = bits_per_pixel;

    f.write(reinterpret_cast<char*>(file_header), file_header_size_);
    f.write(reinterpret_cast<char*>(info_header), info_header_size_);

    const double max_color_value = 255.0;

    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            uint8_t r = static_cast<uint8_t>(image_[i][j].red * max_color_value);
            uint8_t g = static_cast<uint8_t>(image_[i][j].green * max_color_value);
            uint8_t b = static_cast<uint8_t>(image_[i][j].blue * max_color_value);

            uint8_t rgb[] = {b, g, r};
            f.write(reinterpret_cast<char*>(rgb), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding_amount);
    }

    f.close();
}