//
// Created by Alberto Cardini on 11/07/24.
//

#ifndef PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
#define PPM_PHOTO_EDITOR_EDGEDETECTION_HPP

#include "Filter.hpp"
#include "GaussianBlur.hpp"
class EdgeDetection : public Filter{
private:
    std::unique_ptr<Matrix<float>> sobelKernelY;
    std::unique_ptr<Matrix<float>> sobelKernelX;
    void enhance(Image& img);
public:
    EdgeDetection();
    void apply(Image& img) override;
};

#endif  // PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
