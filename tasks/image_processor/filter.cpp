#include "filter.h"

void MatrixFilter::Apply(Image &image) {
    std::vector<std::vector<RGB>> new_image(image.Height(), std::vector<RGB>(image.Width()));
    std::vector<std::vector<double>> matrix;
    for (size_t k = 0; k < GetMatrixVector().size(); ++k) {
        matrix = GetMatrixVector()[k];
        const int64_t zero = 0;
        for (size_t i = 0; i < image.Height(); ++i) {
            for (size_t j = 0; j < image.Width(); ++j) {
                new_image[i][j] = RGB();
                for (int64_t y = -static_cast<int>(matrix.size()) / 2; y < static_cast<int64_t>(matrix.size()) / 2 + 1;
                     ++y) {
                    for (int64_t x = -static_cast<int>(matrix[0].size()) / 2;
                         x < static_cast<int64_t>(matrix[0].size()) / 2 + 1; ++x) {
                        int64_t matrix_x = x + static_cast<int>(matrix[0].size()) / 2;
                        int64_t matrix_y = y + static_cast<int>(matrix.size()) / 2;
                        size_t image_y = std::max(
                            zero, std::min(static_cast<int64_t>(image.Height()) - 1, static_cast<int64_t>(i) + y));
                        size_t image_x = std::max(
                            zero, std::min(static_cast<int64_t>(image.Width()) - 1, static_cast<int64_t>(j) + x));
                        new_image[i][j] += matrix[matrix_y][matrix_x] * image[image_y][image_x];
                    }
                }
                    new_image[i][j].Normalize();
            }
        }
        image.ReplaceImage(new_image);
    }
}
