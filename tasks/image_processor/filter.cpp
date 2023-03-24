#include "filter.h"

//void MatrixFilter::Apply(Image &image) {
//    std::vector<std::vector<int>> matrix = GetMatrix();
//    std::vector<std::vector<RGB>> new_image(image.Height(), std::vector<RGB>(image.Width()));
//    for (int i = 0; i < image.Height(); ++i) {
//        for (int j = 0; j < image.Width(); ++j) {
//            for (int x = -static_cast<int>(matrix.size()) / 2;  x < matrix.size() / 2; ++x) {
//                for (int y = -static_cast<int>(matrix[0].size()) / 2;  y < matrix.size() / 2; ++y) {
//                    new_image[i][j] += matrix[x + static_cast<int>(matrix.size()) / 2][y + static_cast<int>(matrix[0].size()) / 2] *
//                                       image[std::max(0, std::min(image.Height() - 1, i + x))][std::max(0, std::min(image.Height() - 1, j + y))];
//                }
//            }
//            new_image[i][j].Normalize();
//        }
//    }
//    image.ReplaceImage(new_image);
//}