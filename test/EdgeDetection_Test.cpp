//
// Created by Alberto Cardini on 29/08/24.
//
#include "Edge_Detection.hpp"
#include "gtest/gtest.h"

class EdgeDetection_Test : public testing::Test, public Edge_Detection {
protected:
    EdgeDetection_Test() : Edge_Detection(60, 20), i1("../test_asset/test.ppm") {}
    void SetUp() override {
        calc_gradient_magnitude(*i1.get_gray_scale_bitmap());
        calc_gradient_direction(*i1.get_gray_scale_bitmap());
    }
    Image i1;
};

TEST_F(EdgeDetection_Test, grad_direction_test) {
    ASSERT_EQ(low_threshold, 20);
    ASSERT_EQ(high_threshold, 60);

    for (int i = 0; i < i1.get_height() * i1.get_width(); ++i) {
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
    ASSERT_EQ(gradient_magnitude->get_matrix().size(),
              i1.get_width() * i1.get_height());
}

TEST_F(EdgeDetection_Test, hysteresis_test) {
    edge_tracking_by_hysteresis();
    ASSERT_EQ(gradient_magnitude->get_matrix().size(),
              i1.get_width() * i1.get_height());
}

TEST_F(EdgeDetection_Test, dummy_img_test) {
    Matrix<int> dummy(15,14);
    std::vector<int> values = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 ,255,255, 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 ,255,255,255,255, 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 ,255,255, 0 , 0 ,255,255, 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 ,255,255, 0 , 0 , 0 , 0 ,255,255, 0 , 0 , 0 ,
                                0 , 0 , 0 ,255, 0 , 0 , 0 , 0 , 0 , 0 ,255, 0 , 0 , 0 ,
                                0 , 0 , 0 ,255,255, 0 , 0 , 0 , 0 ,255,255, 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 ,255,255, 0 , 0 ,255,255, 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 ,255,255,255,255, 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 ,255,255, 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
                                0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };

    dummy.insert(values);

    calc_gradient_magnitude(dummy);
    calc_gradient_direction(dummy);

    for (int i = 0; i < 15 * 14; ++i) {
        ASSERT_LE((*gradient_direction)[i], 180);
        ASSERT_GE((*gradient_magnitude)[i], 0);
    }

    lower_bound_cut_off_suppression();


    for (int i = 0; i < 15 * 14; ++i) {
        if ((*gradient_magnitude)[i] == 0 || (*gradient_magnitude)[i] > 1000) {
            SUCCEED();
        } else {
            FAIL();
        }
    }

    lower_thresholding();

    for (int i = 0; i < 15 * 14; ++i) {
        if ((*gradient_magnitude)[i] < low_threshold) {
            ASSERT_EQ((*gradient_magnitude)[i], 0);
        }
    }

    edge_tracking_by_hysteresis();

    for (int i = 0; i < 15 * 14; ++i) {
        if ((*gradient_magnitude)[i] < high_threshold) {
            ASSERT_EQ((*gradient_magnitude)[i], 0);
        }
    }

}
