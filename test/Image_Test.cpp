//
// Created by Alberto Cardini on 29/08/24.
//
#include "Image.hpp"
#include "gtest/gtest.h"

class Image_Test : public testing::Test {
public:
    Image_Test() {
        img_test = std::make_unique<Image>("../input/sunflower.ppm");
    };
private:
    std::unique_ptr<Image> img_test;
};


TEST_F(Image_Test, loadTest) {
    ASSERT_EQ(0,0);
}

/*
TEST_F(Image_Test, saveTest) {}
TEST_F(Image_Test, valueCheckTest) {}
*/