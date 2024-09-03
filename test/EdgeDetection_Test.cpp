//
// Created by Alberto Cardini on 29/08/24.
//
#include "EdgeDetection.hpp"

#include "gtest/gtest.h"

class EdgeDetection_Test : public testing::Test, public EdgeDetection {
protected:
    EdgeDetection_Test() : EdgeDetection(60, 20), i1("../test_asset/test.ppm") {}
    void SetUp() override {
        calc_gradient_magnitude(*i1.getGrayScaleBitmap());
        calc_gradient_direction(*i1.getGrayScaleBitmap());
    }
    Image i1;
};

TEST_F(EdgeDetection_Test, grad_direction_test) {
    ASSERT_EQ(low_threshold, 20);
    ASSERT_EQ(high_threshold, 60);

    for (int i = 0; i < i1.getHeight() * i1.getWidth(); ++i) {
        ASSERT_LE((*gradient_direction)[i], 180);
        ASSERT_GE((*gradient_magnitude)[i], 0);

        switch ((*gradient_direction)[i]) {
            case 0  : SUCCEED();
                break;
            case 45 : SUCCEED();
                break;
            case 90 : SUCCEED();
                break;
            case 135: SUCCEED();
                break;
            default : FAIL();
        }
    }
}

TEST_F(EdgeDetection_Test, suppresssion_test) {
    lower_bound_cut_off_suppression();
    ASSERT_EQ(gradient_magnitude->getMatrix().size(), i1.getWidth() * i1.getHeight());
}

TEST_F(EdgeDetection_Test, hysteresis_test) {
    edge_tracking_by_hysteresis();
    ASSERT_EQ(gradient_magnitude->getMatrix().size(), i1.getWidth() * i1.getHeight());
}