//
// Created by Alberto Cardini on 11/07/24.
//

#ifndef PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
#define PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
#include <memory>
#include "Filter.hpp"
#include "GaussianBlur.hpp"
#include "Gray_Scale_image.hpp"
class EdgeDetection : public Filter{
private:

    void calc_gradient_magnitude(Matrix<int>& bitmap);
    void calc_gradient_direction(Matrix<int>& bitmap);
    void lower_bound_cut_off_suppression();
    void lower_thresholding(float low_threshold) const;
    void edge_tracking_by_hysteresis(float high_threshold);

    std::unique_ptr<Matrix<float>> sobel_Y_1;
    std::unique_ptr<Matrix<float>> sobel_Y_2;

    std::unique_ptr<Matrix<float>> sobel_X_1;
    std::unique_ptr<Matrix<float>> sobel_X_2;

    std::unique_ptr<Matrix<float>> gradient_magnitude;
    std::unique_ptr<Matrix<int>> gradient_direction;

public:
    EdgeDetection();
    void apply(Gray_Scale_image& img) override;
    void apply(RGB_image& img) override;
};

#endif  // PPM_PHOTO_EDITOR_EDGEDETECTION_HPP
