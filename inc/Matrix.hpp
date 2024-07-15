//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_MATRIX_HPP
#define MINIPHOTOEDITOR_MATRIX_HPP
#include <iostream>
#include <vector>

template <typename T, typename N = float>
class Matrix {
public:
    Matrix(int h, int w) : row(h), columns(w) { matrix.reserve(row * columns); }

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
            row     = right.row;
            columns = right.columns;
            matrix  = right.matrix;
        }
        return *this;
    }

    void insertWithRound(Matrix<N>& right) {
        if (row == right.getRow() && columns == right.getColumns()){
            for (int i = 0; i < row * columns; ++i) {
                matrix[i] = right.getMatrix()[i];
            }
        }
    };

    T arithmeticAvg() {
        T temp = 0;
        for (int i = 0; i < row * columns; ++i) { temp = (temp + matrix[i]); }
        temp = temp / (row * columns);
        return temp;
    }

    void convolve(Matrix<N>& h) {
        if (h.getRow() % 2 == 1 && h.getColumns() % 2 == 1) {
            int       plusRow     = h.getRow() / 2;
            int       plusColumns = h.getColumns() / 2;
            Matrix<T> convolved_M(row, columns);
            padVector(plusRow, plusColumns, arithmeticAvg());
            h.flipAxisY();
            h.flipAxisX();
            float temp = 0;
            for (int i = 0; i < row - (plusRow * 2); ++i) {
                for (int j = 0; j < columns - (plusColumns * 2); ++j) {
                    for (int m = 0; m < h.getRow() * h.getColumns(); ++m) {
                        temp += matrix[columns * (i + (m % h.getRow())) + j + (m % h.getColumns())] * h.getMatrix()[m];
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
            for (int j = 0; j < columns; ++j) {
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

    void padVector(int plusRow, int plusColumns, T padding) {
        int newHeight = row + plusRow * 2;
        int newWidth  = columns + plusColumns * 2;

        Matrix<T>      newMatrix(newHeight, newWidth);
        std::vector<T> paddedVector;
        paddedVector.reserve(newHeight * newWidth);

        for (int i = 0; i < newHeight * newWidth; ++i) {
            paddedVector.push_back(padding);
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < columns; ++j) {
                paddedVector[newWidth * (i + plusRow) + (j + plusColumns)] =
                    matrix[columns * i + j];
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
