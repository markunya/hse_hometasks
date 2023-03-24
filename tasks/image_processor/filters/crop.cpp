#include "crop.h"

Crop::Crop(uint32_t width, uint32_t height) : width_(width), height_(height) {
}

void Crop::Apply(Image& image) {
    std::vector<std::vector<RGB>> new_image(Height(), std::vector<RGB>(Width()));
    for (size_t i = 0; i < Height(); ++i) {
        for (size_t j = 0; j < Width(); ++j) {
            new_image[i][j] = image[i + image.Height() - Height()][j];
        }
    }
    image.ReplaceImage(new_image);
    image.Resize(Width(), Height());
}

uint32_t Crop::Width() const {
    return width_;
}

uint32_t Crop::Height() const {
    return height_;
}

