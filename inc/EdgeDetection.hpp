//
// Created by Alberto Cardini on 11/07/24.
//

#ifndef PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
#define PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
#include <memory>
#include "Filter.hpp"
#include "GaussianBlur.hpp"
#include "Image.hpp"
class EdgeDetection : public Filter{
protected:

    void calc_gradient_magnitude(Matrix<int>& bitmap);
    void calc_gradient_direction(Matrix<int>& bitmap);
    void lower_bound_cut_off_suppression();
    void lower_thresholding() const;
    void edge_tracking_by_hysteresis() const;

    float high_threshold;
    float low_threshold;

    std::unique_ptr<Matrix<float>> sobel_Y_1;
    std::unique_ptr<Matrix<float>> sobel_Y_2;

    std::unique_ptr<Matrix<float>> sobel_X_1;
    std::unique_ptr<Matrix<float>> sobel_X_2;

    std::unique_ptr<Matrix<float>> gradient_magnitude;
    std::unique_ptr<Matrix<int>> gradient_direction;

public:
    EdgeDetection(float h, float l);
    void apply(Image& img) override;
};

#endif  // PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
