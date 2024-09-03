//
// Created by Alberto Cardini on 11/07/24.
//
#include "Gaussian_Blur.hpp"

Gaussian_Blur::Gaussian_Blur(int s) : sigma(s) {
    variance = pow(sigma, 2);

    if (static_cast<int>((2 * M_PI * sigma)) % 2 == 0) {
        kernel_Y_section = std::make_unique<Matrix<float>>(2 * M_PI * sigma + 1, 1);
        kernel_X_section = std::make_unique<Matrix<float>>(1,2 * M_PI * sigma + 1);
    }
    else{
        kernel_Y_section = std::make_unique<Matrix<float>>(2 * M_PI * sigma,1);
        kernel_X_section = std::make_unique<Matrix<float>>(1,2 * M_PI * sigma);
    }

    for (int i = 0; i < kernel_Y_section->get_row(); ++i) {
        kernel_Y_section->insert((1 / (sqrt(2 * M_PI) * sigma)) * exp((pow((-kernel_Y_section->get_row() / 2) + i, 2)) / (-2 * variance)));
        kernel_X_section->insert((1 / (sqrt(2 * M_PI) * sigma)) * exp((pow((-kernel_X_section->get_columns() / 2) + i, 2)) / (-2 * variance)));
    }

}

void Gaussian_Blur::apply(Image& img) {
    img.get_bitmap_R()->convolve(*kernel_Y_section);
    img.get_bitmap_G()->convolve(*kernel_Y_section);
    img.get_bitmap_B()->convolve(*kernel_Y_section);

    img.get_bitmap_R()->convolve(*kernel_X_section);
    img.get_bitmap_G()->convolve(*kernel_X_section);
    img.get_bitmap_B()->convolve(*kernel_X_section);
}
