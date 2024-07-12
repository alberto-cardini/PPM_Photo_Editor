//
// Created by Alberto Cardini on 11/07/24.
//
#include "GaussianBlur.hpp"

GaussianBlur::GaussianBlur(int s) : sigma(s) {
    variance   = pow(sigma, 2);
    if (static_cast<int>((2 * M_PI * variance)) % 2 == 0)
        kernel     = std::make_unique<Matrix<float>>(2 * M_PI * variance + 2, 2 * M_PI * variance + 1);
    else
        kernel     = std::make_unique<Matrix<float>>(2 * M_PI * variance, 2 * M_PI * variance);
    kernelSize = kernel->getRow();

    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel->insert(
                (1.0/(2 * M_PI * variance)) * exp((pow((-kernelSize / 2) + i, 2) + pow((-kernelSize / 2) + j, 2)) / (-2 * variance)));
        }
    }

    for (int i = 0; i < kernelSize * kernelSize; ++i) {
        weightSum = weightSum + (*kernel)[i];
    }

    kernel->flipAxisY();
    kernel->flipAxisX();

    kernelYSection = std::make_unique<Matrix<float>>(kernelSize, 1);

    for (int i = 0; i < kernelYSection->getRow(); ++i) {
        kernelYSection->insert((*kernel)[kernelSize * i + kernelSize / 2]);
    }

    kernelXSection = std::make_unique<Matrix<float>>(1, kernelSize);

    for (int i = 0; i < kernelSize; ++i) {
        kernelXSection->insert((*kernel)[(kernelSize / 2) * kernelSize + i]);
    }
}

void GaussianBlur::apply(Image &img) {
    /*
    img.getBitmap_R()->convolve(*kernelYSection);
    img.getBitmap_G()->convolve(*kernelYSection);
    img.getBitmap_B()->convolve(*kernelYSection);

    img.getBitmap_R()->convolve(*kernelXSection);
    img.getBitmap_G()->convolve(*kernelXSection);
    img.getBitmap_B()->convolve(*kernelXSection);*/

    img.getBitmap_R()->convolve(*kernel);
    img.getBitmap_G()->convolve(*kernel);
    img.getBitmap_B()->convolve(*kernel);
}

/*
Matrix<int> GaussianBlur::applyFilter(Matrix<int>& bitmap) {
    if (kernel->getHeight() % 2 == 1 &&
        kernel->getWidth() % 2 == 1) {
        int         plus =
            kernel->getWidth() - (kernel->getWidth() / 2 + 1);
        Matrix<int> convolved_M(bitmap.getHeight(), bitmap.getWidth());
        bitmap.reallocate(plus, bitmap.arithmeticAvg());

        double temp = 0;
        for (int i = 0; i < bitmap.getHeight() - (plus * 2); ++i) {
            for (int j = 0; j < bitmap.getColumns() - (plus * 2); ++j) {
                for (int m = 0; m < kernelYSection->getHeight(); ++m) {
                        temp = temp +
                               kernel
                                       ->getMatrix()[kernel->getHeight() *
(i + m) + j + n] * kernel->getMatrix()[kernel->getRow() * m + n];
                }
                convolved_M.matrix.push_back(temp);
                temp = 0;
            }
        }
        *this = convolved_M;
    }
}*/
