//
// Created by Alberto Cardini on 30/08/24.
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

TEST(Matrix_Test, constructor) {
    Matrix<int> test(100,100);
    ASSERT_EQ(test.getRow(), 100);
    ASSERT_EQ(test.getColumns(), 100);
    ASSERT_EQ(test.getRow() * test.getColumns(), test.getMatrix().capacity());
}

TEST(Matrix_Test, insert) {
    Matrix<int> test(0,0);
    int big_number = 10000;
    for (int i = 0; i < big_number; ++i) {
        test.insert(i);
    }
    ASSERT_EQ(test.getMatrix().size(), big_number);
    ASSERT_NE(test.getMatrix().size(), 0);

    for (int i = 0; i < big_number; ++i) {
        ASSERT_EQ(test[i], i);
    }
}

TEST(Matrix_Test, EQ_operator) {
    Matrix<int> new_matrix(20,20);
    Matrix<int> old_matrix(100,100);
    old_matrix = new_matrix;
    ASSERT_EQ(old_matrix.getColumns(), new_matrix.getColumns());
    ASSERT_EQ(old_matrix.getRow(), new_matrix.getRow());
    ASSERT_EQ(old_matrix.getMatrix(), new_matrix.getMatrix());
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

    test.flipAxisY();
    std::vector<int> values_flipped = {3,2,1,
                                       6,5,4,
                                       9,8,7};
    ASSERT_EQ(test.getMatrix(), values_flipped);
}

TEST(Matrix_Test, flipAxisX) {
    Matrix<int> test(3,3);
    std::vector<int> values = {1,2,3,
                               4,5,6,
                               7,8,9};
    test.insert(values);
    test.flipAxisX();
    std::vector<int> values_flipped = {7,8,9,
                                       4,5,6,
                                       1,2,3};
    ASSERT_EQ(test.getMatrix(), values_flipped);
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
    ASSERT_EQ(test.getMatrix(), values_result);
}

TEST(Matrix_Test, padding) {
    Matrix<int> test(3,3);
    std::vector<int> values = {9,9,9,
                               9,9,9,
                               9,9,9};
    test.insert(values);
    test.padVector(1,1,0);
    Matrix<int> result(5,5);
    std::vector<int> values_result = {0,0,0,0,0,
                                      0,9,9,9,0,
                                      0,9,9,9,0,
                                      0,9,9,9,0,
                                      0,0,0,0,0};
    result.insert(values_result);
    ASSERT_EQ(test.getMatrix(), values_result);
}