#include "edge_detection.h"
#include "gray_scale.h"

EdgeDetection::EdgeDetection(const double& threshold) : threshold_(threshold) {
}

void EdgeDetection::Apply(Image& image) {
    GrayScale gs;
    gs.Apply(image);
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
