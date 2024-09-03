//
// Created by Alberto Cardini on 11/07/24.
//

#ifndef PPM_PHOTO_EDITOR_GAUSSIAN_BLUR_HPP
#define PPM_PHOTO_EDITOR_GAUSSIAN_BLUR_HPP
#include "Filter.hpp"

class Gaussian_Blur : public Filter {
private:
    std::unique_ptr<Matrix<float>> kernel_Y_section;
    std::unique_ptr<Matrix<float>> kernel_X_section;

    int                            sigma;
    int                            variance;

public:
    explicit Gaussian_Blur(int s);
    void apply(Image& img) override;
};

#endif  // PPM_PHOTO_EDITOR_GAUSSIAN_BLUR_HPP