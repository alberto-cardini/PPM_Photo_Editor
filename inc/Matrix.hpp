//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_MATRIX_HPP
#define MINIPHOTOEDITOR_MATRIX_HPP
#include <iostream>
#include <vector>
#include "Pixel.hpp"

template <typename T>
class Matrix {
public:
    Matrix(int h, int w) : height(h), width(w) {
        matrix.reserve(height * width);
    }

    int  getHeight() const { return height; }
    int  getWidth() const { return width; }

    void insertValue(const std::vector<T>& valuesArray) {
        if (valuesArray.size() == height * width)
            for (int i = 0; i < height * width; ++i) {
                matrix.push_back(valuesArray[i]);
            }
    }

    void insertValue(const T& value) {
        try {
            matrix.push_back(value);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    Matrix<T>& operator=(const Matrix<T>& right) {
        if (this == *right) {
            height = right.height;
            width  = right.width;
            matrix = right.matrix;
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& right) {
        Matrix<T> result(height, width);
        for (int i = 0; i < height * width; ++i) {
            result.matrix.push_back(matrix[i] + right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& right) {
        Matrix<T> result(height, width);
        for (int i = 0; i < height * width; ++i) {
            result.matrix.push_back(matrix[i] - right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& right) {
        Matrix<T> result(height, width);
        for (int i = 0; i < height * width; ++i) {
            result.matrix.push_back(matrix[i] * right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator/(const Matrix<T>& right) {
        Matrix<T> result(height, width);
        for (int i = 0; i < height * width; ++i) {
            result.matrix.push_back(matrix[i] / right.matrix[i]);
        }
        return result;
    }

    T average() {
        T temp = 0;
        for (int i = 0; i < height * width; ++i) { temp = (temp + matrix[i]); }
        temp = temp / (height * width);
        return temp;
    }

    T convolve(const Matrix<T>& right) {
        if (right.height % 2 == 1 && right.width % 2 == 1) {
            reallocate(right.height - (right.height / 2), right.average());

            // TODO: Implement the convolution
        }
    }

    // Works only with square matrix.
    void reallocate(int plus, T filler) {
        int newHeight           = height + plus * 2;
        // add the plus * 2 extra lines to the matrix. This is needed to create
        // the extra space for the convolution of the first element, otherwise
        // the index of the h(x - tau) would go out of range
        int            newWidth = width + plus * 2;  // same with the columns

        std::vector<T> newMatrix;
        newMatrix.reserve(newHeight * newWidth);

        for (int i = 0; i < newHeight * newWidth; ++i) {
            newMatrix.push_back(filler);
        }

        for (int i = plus; i < newHeight - plus; ++i) {
            for (int j = plus; j < height + plus; ++j) {
                newMatrix[newHeight * i + j] =
                    matrix[height * (i - plus) + (j - plus)];
            }
        }

        matrix = newMatrix;
        height = newHeight;
        width  = newWidth;
    };

    T& operator[](int position) { return matrix.at(position); }

private:
    std::vector<T> matrix;
    int            height;
    int            width;
};

#endif  // MINIPHOTOEDITOR_MATRIX_HPP
