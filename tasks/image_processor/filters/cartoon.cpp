#include "cartoon.h"
#include "gausian_blur.h"
#include "edge_detection.h"

void Cartoon::Apply(Image& image) {
    const double blur_sigma = 3.2;
    const double threshold = 0.0018;
    const double number_close_to_one = 0.9;
    const double opacity_of_detection = 0.33;
    GaussianBlur blur(blur_sigma);
    blur.Apply(image);
    Image new_layer = image;
    EdgeDetection edge(threshold);
    edge.Apply(new_layer);
    blur.Apply(image);
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            if (new_layer[i][j].red > number_close_to_one)  {
                image[i][j] = RGB() + image[i][j] * opacity_of_detection;
            }
        }
    }
}
