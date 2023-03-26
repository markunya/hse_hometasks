#include "edge_detection.h"

EdgeDetection::EdgeDetection(const double& threshold) : threshold_(threshold) {
}

void EdgeDetection::Apply(Image& image) {
    const double c_1 = 0.299;
    const double c_2 = 0.587;
    const double c_3 = 0.114;
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            image[i][j] = RGB(c_1 * image[i][j].red + c_2 * image[i][j].green + c_3 * image[i][j].blue);
        }
    }
    MatrixFilter::Apply(image);
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            if (image[i][j].red > threshold_) {
                image[i][j] = RGB(1.0, 1.0, 1.0);
            } else {
                image[i][j] = RGB();
            }
        }
    }
}
const std::vector<std::vector<std::vector<double>>>& EdgeDetection::GetMatrixVector() const {
    return matrix_vector_;
}
