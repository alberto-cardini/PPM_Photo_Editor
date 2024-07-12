//
// Created by Alberto Cardini on 11/07/24.
//

#ifndef PPM_PHOTO_EDITOR_GAUSSIANBLUR_HPP
#define PPM_PHOTO_EDITOR_GAUSSIANBLUR_HPP
#include "Filter.hpp"

class GaussianBlur : public Filter {
private:
    std::unique_ptr<Matrix<float>> kernel;
    std::unique_ptr<Matrix<float>> kernelYSection;
    std::unique_ptr<Matrix<float>> kernelXSection;

    int                             sigma;
    int                             variance;
    int                             kernelSize;  // square matrix n x n
    double                          weightSum{0};

public:
    explicit GaussianBlur(int s);
    auto& getMatrix() { return kernel; };
    void  apply(Image& img) override;
};

#endif  // PPM_PHOTO_EDITOR_GAUSSIANBLUR_HPP
