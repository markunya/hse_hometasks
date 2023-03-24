#include "gray_scale.h"

void GrayScale::Apply(Image& image) {
    const double c_1 = 0.299;
    const double c_2 = 0.587;
    const double c_3 = 0.114;
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            image[i][j] = RGB(c_1 * image[i][j].red + c_2 * image[i][j].green + c_3 * image[i][j].blue);
        }
    }
}
