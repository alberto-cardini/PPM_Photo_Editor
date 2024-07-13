//
// Created by Alberto Cardini on 11/07/24.
//
#include "GaussianBlur.hpp"

GaussianBlur::GaussianBlur(int s) : sigma(s) {
    variance = pow(sigma, 2);

    if (static_cast<int>((2 * M_PI * sigma)) % 2 == 0) {
        kernelYSection = std::make_unique<Matrix<float>>(2 * M_PI * sigma + 1, 1);
        kernelXSection = std::make_unique<Matrix<float>>(1,2 * M_PI * sigma + 1);
    }
    else{
        kernelYSection = std::make_unique<Matrix<float>>(2 * M_PI * sigma,1);
        kernelXSection = std::make_unique<Matrix<float>>(1,2 * M_PI * sigma);
    }

    for (int i = 0; i < kernelYSection->getRow(); ++i) {
        kernelYSection->insert((1 / (sqrt(2 * M_PI) * sigma)) * exp((pow((-kernelYSection->getRow() / 2) + i, 2)) / (-2 * variance)));
        kernelXSection->insert((1 / (sqrt(2 * M_PI) * sigma)) * exp((pow((-kernelXSection->getColumns() / 2) + i, 2)) / (-2 * variance)));
    }

}

void GaussianBlur::apply(Image &img) {
    img.getBitmap_R()->convolve(*kernelYSection);
    img.getBitmap_G()->convolve(*kernelYSection);
    img.getBitmap_B()->convolve(*kernelYSection);

    img.getBitmap_R()->convolve(*kernelXSection);
    img.getBitmap_G()->convolve(*kernelXSection);
    img.getBitmap_B()->convolve(*kernelXSection);
}
