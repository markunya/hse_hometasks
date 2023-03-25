#include "filter.h"


void MatrixFilter::Apply(Image &image) {
    std::vector<std::vector<int>> matrix = GetMatrix();
    std::vector<std::vector<RGB>> new_image(image.Height(), std::vector<RGB>(image.Width()));
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            for (int y = -static_cast<int>(matrix.size()) / 2;  y < static_cast<int64_t>(matrix.size()) / 2 + 1; ++y) {
                for (int x = -static_cast<int>(matrix[0].size()) / 2;  x < static_cast<int64_t>(matrix[0].size()) / 2 + 1; ++x) {
                    int matrix_x = x + static_cast<int>(matrix[0].size()) / 2;
                    int matrix_y = y + static_cast<int>(matrix.size()) / 2;
                    size_t image_y = std::max(0ll, std::min(static_cast<int64_t>(image.Height()) - 1, static_cast<int64_t>(i) + y));
                    size_t image_x = std::max(0ll, std::min(static_cast<int64_t>(image.Width()) - 1, static_cast<int64_t>(j) + x));
                    new_image[i][j] += matrix[matrix_y][matrix_x] * image[image_y][image_x];
                }
            }
            new_image[i][j].Normalize();
        }
    }
    image.ReplaceImage(new_image);
}