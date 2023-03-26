#include <catch.hpp>
#include "image.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include "filters/edge_detection.h"
#include "filters/gray_scale.h"
#include "filters/gausian_blur.h"
#include "filters/cartoon.h"
#include "filters/crop.h"

TEST_CASE("IMAGE_PROCESSOR") {
    // READING
    Image image_to_read("../tasks/image_processor/my_test_images/pic_to_read.bmp");
    const double r_0_0 = 0.2;
    const double b_0_0 = 0.56;
    const double r_0_1 = 0.33;
    const double b_0_1 = 0.44;
    const double r_0_2 = 0.46;
    const double b_0_2 = 0.29;
    REQUIRE((image_to_read[0][0] == RGB(r_0_0, 0, b_0_0) &&
             image_to_read[0][1] == RGB(r_0_1, 0, b_0_1) &&
             image_to_read[0][2] == RGB(r_0_2, 0, b_0_2)));

    // EXPORT
    image_to_read.Export("../tasks/image_processor/my_test_images/pic_to_export.bmp");
    Image image_to_check_export("../tasks/image_processor/my_test_images/pic_to_export.bmp");
    REQUIRE((image_to_check_export[0][0] == RGB(r_0_0, 0, b_0_0) &&
             image_to_check_export[0][1] == RGB(r_0_1, 0, b_0_1) &&
             image_to_check_export[0][2] == RGB(r_0_2, 0, b_0_2)));

    // NEGATIVE
    Image im_1("../tasks/image_processor/my_test_images/pic.bmp");
    Image neg_im("../tasks/image_processor/my_test_images/pic_neg.bmp");
    Negative neg_filter;
    neg_filter.Apply(im_1);
    REQUIRE(im_1 == neg_im);

    // SHARPING
    Image im_2("../tasks/image_processor/my_test_images/pic.bmp");
    Image sharp_im("../tasks/image_processor/my_test_images/pic_sharp.bmp");
    Sharpening sharp_filter;
    sharp_filter.Apply(im_2);
    REQUIRE(im_2 == sharp_im);

    // EDGE_DETECTION
    const double threshold = 0.01;
    Image im_3("../tasks/image_processor/my_test_images/pic.bmp");
    Image edge_im("../tasks/image_processor/my_test_images/pic_edge.bmp");
    EdgeDetection edge_filter(threshold);
    edge_filter.Apply(im_3);
    REQUIRE(im_3 == edge_im);

    // GRAY_SCALE
    Image im_4("../tasks/image_processor/my_test_images/pic.bmp");
    Image gs_im("../tasks/image_processor/my_test_images/pic_gs.bmp");
    GrayScale gray_scale_filter;
    gray_scale_filter.Apply(im_4);
    REQUIRE(im_4 == gs_im);

    // BLUR
    const double sigma = 5;
    Image im_5("../tasks/image_processor/my_test_images/pic.bmp");
    Image blur_im("../tasks/image_processor/my_test_images/pic_blur.bmp");
    GaussianBlur blur_filter(sigma);
    blur_filter.Apply(im_5);
    REQUIRE(im_5 == blur_im);

    // CARTOON
    Image im_6("../tasks/image_processor/my_test_images/pic.bmp");
    Image cart_im("../tasks/image_processor/my_test_images/pic_cart.bmp");
    Cartoon cartoon_filter;
    cartoon_filter.Apply(im_6);
    REQUIRE(im_6 == cart_im);

    // CROP
    Image im_7("../tasks/image_processor/my_test_images/pic.bmp");
    Image crop_im("../tasks/image_processor/my_test_images/pic_crop.bmp");
    Crop crop_filter(4, 2);
    crop_filter.Apply(im_7);
    REQUIRE(im_7 == crop_im);
}