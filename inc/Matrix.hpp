//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_MATRIX_HPP
#define MINIPHOTOEDITOR_MATRIX_HPP

#include <iostream>
#include <vector>

template<typename T, typename N = float>
class Matrix {
public:
    Matrix(int h, int w) : rows(h), columns(w) { matrix.reserve(rows * columns); }

    int get_row() const { return rows; }

    int get_columns() const { return columns; }

    auto &get_matrix() { return matrix; };

    void insert(const std::vector<T> &values_array) {
        if (values_array.size() == rows * columns)
            for (int i = 0; i < rows * columns; ++i) {
                matrix.push_back(values_array[i]);
            }
    }

    void insert(const T &value) {
        try {
            matrix.push_back(value);
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    Matrix &operator=(const Matrix<T> &right) {
        if (this != &right) {
            rows = right.rows;
            columns = right.columns;
            matrix = right.matrix;
        }
        return *this;
    }

    void insert_with_round(Matrix<N> &right) {
        if (rows == right.get_row() && columns == right.get_columns()) {
            for (int i = 0; i < rows * columns; ++i) {
                matrix[i] = right.get_matrix()[i];
            }
        }
    };

    T arithmetic_avg() {
        T temp = 0;
        for (int i = 0; i < rows * columns; ++i) { temp = (temp + matrix[i]); }
        temp = temp / (rows * columns);
        return temp;
    }

    void convolve(Matrix<N> &h) {
        if (h.get_row() % 2 == 1 && h.get_columns() % 2 == 1) {
            int plus_row = h.get_row() / 2;
            int plus_columns = h.get_columns() / 2;
            Matrix<T> convolved_m(rows, columns);
            pad_vector(plus_row, plus_columns, arithmetic_avg());
            h.flip_axis_Y();
            h.flip_axis_X();
            float temp = 0;
            for (int i = 0; i < rows - (plus_row * 2); ++i) {
                for (int j = 0; j < columns - (plus_columns * 2); ++j) {
                    for (int m = 0; m < h.get_row() * h.get_columns(); ++m) {
                        temp += matrix[columns * (i + (m % h.get_row())) + j + (m % h.get_columns())] * h.get_matrix()[m];
                    }
                    convolved_m.matrix.push_back(temp);
                    temp = 0;
                }
            }
            *this = convolved_m;
        }
    }

    void flip_axis_X() {
        Matrix<T> flipped_matrix(rows, columns);
        for (int i = rows - 1; i >= 0; --i) {
            for (int j = 0; j < columns; ++j) {
                flipped_matrix.matrix.push_back(matrix[columns * i + j]);
            }
        }
        *this = flipped_matrix;
    }

    void flip_axis_Y() {
        Matrix<T> flipped_matrix(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = columns - 1; j >= 0; --j) {
                flipped_matrix.matrix.push_back(matrix[columns * i + j]);
            }
        }
        *this = flipped_matrix;
    }

    void pad_vector(int plusRow, int plusColumns, T padding) {
        int new_height = rows + plusRow * 2;
        int new_width = columns + plusColumns * 2;

        Matrix<T> new_matrix(new_height, new_width);
        std::vector<T> padded_vector;
        padded_vector.reserve(new_height * new_width);

        for (int i = 0; i < new_height * new_width; ++i) {
            padded_vector.push_back(padding);
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                padded_vector[new_width * (i + plusRow) + (j + plusColumns)] =
                        matrix[columns * i + j];
            }
        }
        new_matrix.insert(padded_vector);
        *this = new_matrix;
    };

    T &operator[](int position) { return matrix.at(position); }

private:
    std::vector<T> matrix;
    int rows;
    int columns;
};

#endif  // MINIPHOTOEDITOR_MATRIX_HPP
