//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_MATRIX_HPP
#define MINIPHOTOEDITOR_MATRIX_HPP
#include <iostream>
#include <vector>

template <typename T, typename N = float >
class Matrix {
public:
    Matrix(int h, int w) : row(h), columns(w) {
        matrix.reserve(row * columns);
    }

    int   getRow() const { return row; }
    int   getColumns() const { return columns; }
    auto& getMatrix() { return matrix; };

    void  insert(const std::vector<T>& valuesArray) {
        if (valuesArray.size() == row * columns)
            for (int i = 0; i < row * columns; ++i) {
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
            row    = right.row;
            columns = right.columns;
            matrix = right.matrix;
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& right) {
        Matrix<T> result(row, columns);
        for (int i = 0; i < row * columns; ++i) {
            result.matrix.push_back(matrix[i] + right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& right) {
        Matrix<T> result(row, columns);
        for (int i = 0; i < row * columns; ++i) {
            result.matrix.push_back(matrix[i] - right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& right) {
        Matrix<T> result(row, columns);
        for (int i = 0; i < row * columns; ++i) {
            result.matrix.push_back(matrix[i] * right.matrix[i]);
        }
        return result;
    }

    Matrix<T> operator/(const T& right) {
        Matrix<T> result(row, columns);
        for (int i = 0; i < row * columns; ++i) {
            result.matrix.push_back(matrix[i] / right);
        }
        return result;
    }

    T arithmeticAvg() {
        T temp = 0;
        for (int i = 0; i < row * columns; ++i) { temp = (temp + matrix[i]); }
        temp = temp / (row * columns);
        return temp;
    }

    void convolve(Matrix<N>& h) {
        if (h.getRow() % 2 == 1 && h.getColumns() % 2 == 1) {
            int       plus = h.getRow() - (h.getColumns() / 2 + 1);
            Matrix<T> convolved_M(row, columns);
            padVector(plus, arithmeticAvg());
            h.flipAxisY();
            h.flipAxisX();
            T temp = 0;
            for (int i = 0; i < row - (plus * 2); ++i) {
                for (int j = 0; j < columns - (plus * 2); ++j) {
                    for (int m = 0; m < h.getRow(); ++m) {
                        for (int n = 0; n < h.getColumns(); ++n) {
                            temp += matrix[columns * (i + m) + j + n] *
                                           h.getMatrix()[h.getColumns() * m + n];
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
        Matrix<T> flippedMatrix(row, columns);
        for (int i = row - 1; i >= 0; --i) {
            for (int j = 0; j < row; ++j) {
                flippedMatrix.matrix.push_back(matrix[columns * i + j]);
            }
        }
        *this = flippedMatrix;
    }

    void flipAxisY() {
        Matrix<T> flippedMatrix(row, columns);
        for (int i = 0; i < row; ++i) {
            for (int j = columns - 1; j >= 0; --j) {
                flippedMatrix.matrix.push_back(matrix[columns * i + j]);
            }
        }
        *this = flippedMatrix;
    }

    // Works only with square kernel.
    void padVector(int plus, T padding) {
        int newHeight           = row + plus * 2;
        // add the plus * 2 extra lines to the kernel. This is needed to create
        // the extra space for the convolution of the first element, otherwise
        // the index of the h(x - tau) would go out of range
        int            newWidth = columns + plus * 2;  // same with the columns

        Matrix<T>      newMatrix(newHeight, newWidth);
        std::vector<T> paddedVector;
        paddedVector.reserve(newHeight * newWidth);

        for (int i = 0; i < newHeight * newWidth; ++i) {
            paddedVector.push_back(padding);
        }

        for (int i = plus; i < row + plus; ++i) {
            for (int j = plus; j < columns + plus; ++j) {
                paddedVector[newWidth * i + j] =
                    matrix[columns * (i - plus) + (j - plus)];
            }
        }
        newMatrix.insert(paddedVector);
        *this = newMatrix;
    };

    T& operator[](int position) { return matrix.at(position); }

private:

    std::vector<T> matrix;
    int            row;
    int            columns;
};

#endif  // MINIPHOTOEDITOR_MATRIX_HPP
