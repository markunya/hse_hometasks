#include "gausian_blur.h"
#include "cmath"

GaussianBlur::GaussianBlur(const double& sigma) {
    std::vector<std::vector<double>> matrix = {};
    double sum = 0;
    const double c = 2.0;
    double element = 0.0;
    matrix.push_back({});
    const int matrix_size = 81;
    for (int i = -matrix_size / 2; i < matrix_size - matrix_size / 2; ++i) {
        element = (exp(-(i * i) / (c * sigma * sigma))) / (sqrt(c * M_PI) * sigma);
        sum += element;
        matrix[0].push_back(element);
    }
    for (size_t i = 0; i < matrix[0].size(); ++i) {
        matrix[0][i] /= sum;
    }
    matrix_vector_.push_back(matrix);
    matrix.clear();
    for (int i = -matrix_size / 2; i < matrix_size - matrix_size / 2; ++i) {
        matrix.push_back({((exp(-(i * i) / (c * sigma * sigma))) / ((sqrt(c * M_PI) * sigma))) / sum});
    }
    matrix_vector_.push_back(matrix);
}

const std::vector<std::vector<std::vector<double>>>& GaussianBlur::GetMatrixVector() const {
    return matrix_vector_;
}

void GaussianBlur::Apply(Image& image) {
    MatrixFilter::Apply(image);
}
