//
// Created by Alberto Cardini on 29/08/24.
//
#include "Image.hpp"
#include "gtest/gtest.h"
/*
class Image_Test : public testing::Test {
public:
    Image_Test() {
        img_test = std::make_unique<Image>("../input/sunflower.ppm");
    };
private:
    std::unique_ptr<Image> img_test;
};
*/

TEST(Image_Test, constructor_load) {
    Image         test("../test_asset/test.ppm");
    std::string   type;
    int           width, height, channelRange;
    std::ifstream input;
    input.open("../test_asset/test.ppm");
    ASSERT_TRUE(input.is_open());

    input >> type;
    input >> width;
    input >> height;
    input >> channelRange;

    ASSERT_EQ(test.get_width(), width);
    ASSERT_EQ(test.get_height(), height);
    ASSERT_EQ(test.get_type(), type);
    ASSERT_EQ(test.get_range(), channelRange);

    std::vector<int> null_vector = {0};

    ASSERT_NE(test.get_bitmap_R()->get_matrix(), null_vector);
    ASSERT_NE(test.get_bitmap_G()->get_matrix(), null_vector);
    ASSERT_NE(test.get_bitmap_B()->get_matrix(), null_vector);

    Image test2("../test_asset/sunflower_gray_scale.pgm");
    for (int i = 0; i < test2.get_height() * test2.get_width(); ++i) {
        ASSERT_EQ(test2.get_bitmap_R()->get_matrix()[i],
                  test2.get_bitmap_G()->get_matrix()[i]);
        ASSERT_EQ(test2.get_bitmap_B()->get_matrix()[i],
                  test2.get_bitmap_G()->get_matrix()[i]);
    }
}

TEST(Image_Test, RGB_to_GS_save_and_get) {
    Image test("../test_asset/test.ppm");
    test.save_gray_scale("../test_asset/test_GS.pgm");

    std::ifstream test_GS;
    test_GS.open("../test_asset/test_GS.pgm");
    ASSERT_TRUE(test_GS.is_open());

    std::string   type;
    int           width, height, channelRange;

    test_GS >> type;
    test_GS >> width;
    test_GS >> height;
    test_GS >> channelRange;

    ASSERT_EQ(400, width);
    ASSERT_EQ(399, height);
    ASSERT_EQ("P2", type);
    ASSERT_EQ(255, channelRange);

    Matrix<int> gs_bitmap = *test.get_gray_scale_bitmap();
    int current_pixel;
    for (int i = 0; i < test.get_width() * test.get_height(); ++i) {
        test_GS >> current_pixel;
        ASSERT_EQ(gs_bitmap.get_matrix()[i], current_pixel);
    }
}

TEST(Image_Test, check_channel_value) {
    std::srand(std::time(0));
    int pixel;
    for (int i = 0; i < 1000; ++i) {
        pixel = std::rand();
        ASSERT_GT(Image::check_channel_value(pixel), 0);
        ASSERT_LE(Image::check_channel_value(pixel), 255);
    }
}

TEST(Image_Test, save) {
    Image test("../test_asset/test.ppm");
    test.save("../test_asset/test_saved.ppm");

    std::ifstream saved_test;
    saved_test.open("../test_asset/test_saved.ppm");
    ASSERT_TRUE(saved_test.is_open());


    std::string   type;
    int           width, height, channelRange;

    saved_test >> type;
    saved_test >> width;
    saved_test >> height;
    saved_test >> channelRange;

    ASSERT_EQ(test.get_width(), width);
    ASSERT_EQ(test.get_height(), height);
    ASSERT_EQ(test.get_type(), type);
    ASSERT_EQ(test.get_range(), channelRange);

    int R,G,B;

    for (int i = 0; i < test.get_height() * test.get_width(); ++i) {
        saved_test >> R;
        saved_test >> G;
        saved_test >> B;

        ASSERT_EQ(test.get_bitmap_R()->get_matrix()[i], R);
        ASSERT_EQ(test.get_bitmap_G()->get_matrix()[i], G);
        ASSERT_EQ(test.get_bitmap_B()->get_matrix()[i], B);
    }
}