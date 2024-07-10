//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_MATRIX_HPP
#define MINIPHOTOEDITOR_MATRIX_HPP
#include <iostream>
#include <vector>

template <typename T, typename N = double>
class Matrix {
public:
    Matrix(int h, int w) : height(h), width(w) {
        matrix.reserve(height * width);
    }

    int   getHeight() const { return height; }
    int   getWidth() const { return width; }
    auto& getMatrix() { return matrix; };

    void  insert(const std::vector<T>& valuesArray) {
        if (valuesArray.size() == height * width)
            for (int i = 0; i < height * width; ++i) {
                matrix.push_back(valuesArray[i]);
            }
    }

    void insert(const T& value) {
        try {
            matrix.push_back(value);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    Matrix& operator=(const Matrix<T>& right) {
        if (this != &right) {
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

    T arithmeticAvg() {
        T temp = 0;
        for (int i = 0; i < height * width; ++i) { temp = (temp + matrix[i]); }
        temp = temp / (height * width);
        return temp;
    }

    void convolve(Matrix<N>& h) {
        if (h.getHeight() % 2 == 1 && h.getWidth() % 2 == 1) {
            int       plus = h.getWidth() - (h.getWidth() / 2 + 1);
            Matrix<T> convolved_M(height, width);
            reallocate(plus, arithmeticAvg());
            h.flipAxisY();
            h.flipAxisX();
            T temp = 0;
            for (int i = 0; i < height - (plus * 2); ++i) {
                for (int j = 0; j < width - (plus * 2); ++j) {
                    for (int m = 0; m < h.getHeight(); ++m) {
                        for (int n = 0; n < h.getWidth(); ++n) {
                            temp =
                                temp + matrix[height * (i + m) + j + n] *
                                           h.getMatrix()[h.getHeight() * m + n];
                        }
                    }
                    convolved_M.matrix.push_back(temp);
                    temp = 0;
                }
            }
            *this = convolved_M;
        }
    }

    void flipAxisX() {
        Matrix<T> flippedMatrix(height, width);
        for (int i = height - 1; i >= 0; --i) {
            for (int j = 0; j < height; ++j) {
                flippedMatrix.matrix.push_back(matrix[height * i + j]);
            }
        }
        *this = flippedMatrix;
    }

    void flipAxisY() {
        Matrix<T> flippedMatrix(height, width);
        for (int i = 0; i < height; ++i) {
            for (int j = width - 1; j >= 0; --j) {
                flippedMatrix.matrix.push_back(matrix[height * i + j]);
            }
        }
        *this = flippedMatrix;
    }

    // Works only with square kernel.
    void reallocate(int plus, T filler) {
        int newHeight           = height + plus * 2;
        // add the plus * 2 extra lines to the kernel. This is needed to create
        // the extra space for the convolution of the first element, otherwise
        // the index of the h(x - tau) would go out of range
        int            newWidth = width + plus * 2;  // same with the columns

        Matrix<T>      newMatrix(newHeight, newWidth);
        std::vector<T> filledVector;
        filledVector.reserve(newHeight * newWidth);

        for (int i = 0; i < newHeight * newWidth; ++i) {
            filledVector.push_back(filler);
        }

        for (int i = plus; i < newHeight - plus; ++i) {
            for (int j = plus; j < height + plus; ++j) {
                filledVector[newHeight * i + j] =
                    matrix[height * (i - plus) + (j - plus)];
            }
        }
        newMatrix.insert(filledVector);
        *this = newMatrix;
    };

    T& operator[](int position) { return matrix.at(position); }

private:

    std::vector<T> matrix;
    int            height;
    int            width;
};

#endif  // MINIPHOTOEDITOR_MATRIX_HPP
