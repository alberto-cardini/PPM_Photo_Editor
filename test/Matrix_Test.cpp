//
// Created by Alberto Cardini on 30/08/24.
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

TEST(Matrix_Test, constructor) {
    Matrix<int> test(100,100);
    ASSERT_EQ(test.get_row(), 100);
    ASSERT_EQ(test.get_columns(), 100);
    ASSERT_EQ(test.get_row() * test.get_columns(),
              test.get_matrix().capacity());
}

TEST(Matrix_Test, insert) {
    Matrix<int> test(0,0);
    int big_number = 10000;
    for (int i = 0; i < big_number; ++i) {
        test.insert(i);
    }
    ASSERT_EQ(test.get_matrix().size(), big_number);
    ASSERT_NE(test.get_matrix().size(), 0);

    for (int i = 0; i < big_number; ++i) {
        ASSERT_EQ(test[i], i);
    }
}

TEST(Matrix_Test, EQ_operator) {
    Matrix<int> new_matrix(20,20);
    Matrix<int> old_matrix(100,100);
    old_matrix = new_matrix;
    ASSERT_EQ(old_matrix.get_columns(), new_matrix.get_columns());
    ASSERT_EQ(old_matrix.get_row(), new_matrix.get_row());
    ASSERT_EQ(old_matrix.get_matrix(), new_matrix.get_matrix());
    ASSERT_NE(&old_matrix, &new_matrix);
}

TEST(Matrix_Test, flipAxisY) {
    Matrix<int> test(3,3);
    std::vector<int> values = {1,2,3,
                               4,5,6,
                               7,8,9};
    test.insert(values);
    for (int i = 0; i < 9; ++i) {
        ASSERT_EQ(test[i], i + 1);
    }

    test.flip_axis_Y();
    std::vector<int> values_flipped = {3,2,1,
                                       6,5,4,
                                       9,8,7};
    ASSERT_EQ(test.get_matrix(), values_flipped);
}

TEST(Matrix_Test, flipAxisX) {
    Matrix<int> test(3,3);
    std::vector<int> values = {1,2,3,
                               4,5,6,
                               7,8,9};
    test.insert(values);
    test.flip_axis_X();
    std::vector<int> values_flipped = {7,8,9,
                                       4,5,6,
                                       1,2,3};
    ASSERT_EQ(test.get_matrix(), values_flipped);
}

TEST(Matrix_Test, convolve) {
    Matrix<int> test(5,5);
    std::vector<int> values = {9,9,9,9,9,
                               9,9,9,9,9,
                               9,9,9,9,9,
                               9,9,9,9,9,
                               9,9,9,9,9};
    test.insert(values);

    Matrix<float> to_convolve(3,3);
    std::vector<float> value = {0,0,0,
                                0,1,0,
                                0,0,0};
    to_convolve.insert(value);
    test.convolve(to_convolve);

    Matrix<int> result(5,5);
    std::vector<int> values_result = {9,9,9,9,9,
                                      9,9,9,9,9,
                                      9,9,9,9,9,
                                      9,9,9,9,9,
                                      9,9,9,9,9};
    result.insert(values_result);
    ASSERT_EQ(test.get_matrix(), values_result);
}

TEST(Matrix_Test, padding) {
    Matrix<int> test(3,3);
    std::vector<int> values = {9,9,9,
                               9,9,9,
                               9,9,9};
    test.insert(values);
    test.pad_vector(1, 1, 0);
    Matrix<int> result(5,5);
    std::vector<int> values_result = {0,0,0,0,0,
                                      0,9,9,9,0,
                                      0,9,9,9,0,
                                      0,9,9,9,0,
                                      0,0,0,0,0};
    result.insert(values_result);
    ASSERT_EQ(test.get_matrix(), values_result);
}