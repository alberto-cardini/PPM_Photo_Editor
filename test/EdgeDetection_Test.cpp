//
// Created by Alberto Cardini on 29/08/24.
//
#include "gtest/gtest.h"
#include "EdgeDetection.hpp"

class EdgeDetection_Test : public testing::Test {
public:
    EdgeDetection_Test();
private:
    EdgeDetection filter;
};
/*
TEST_F(EdgeDetection_Test, calc_magnitude_test) {}
TEST_F(EdgeDetection_Test, calc_direction_test) {}
TEST_F(EdgeDetection_Test, bound_cut_off_test) {}
TEST_F(EdgeDetection_Test, thresholding_test) {}
TEST_F(EdgeDetection_Test, hysteresis_test) {}
 */