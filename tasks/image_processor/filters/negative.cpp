#include "negative.h"

void Negative::Apply(Image& image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            image[i][j].Inverse();
        }
    }
}