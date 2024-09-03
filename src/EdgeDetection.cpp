//
// Created by Alberto Cardini on 11/07/24.
//

#include "Edge_Detection.hpp"
Edge_Detection::Edge_Detection(float h, float l) : high_threshold(h), low_threshold(l) {
    sobel_X_1                          = std::make_unique<Matrix<float>>(3, 1);
    sobel_X_2                          = std::make_unique<Matrix<float>>(1, 3);

    sobel_Y_1                          = std::make_unique<Matrix<float>>(3, 1);
    sobel_Y_2                          = std::make_unique<Matrix<float>>(1, 3);

    std::vector<float> sobel_base_down = {1, 0, -1};
    std::vector<float> sobel_base_up   = {1, 2, 1};

    sobel_X_1->insert(sobel_base_down);
    sobel_X_2->insert(sobel_base_up);

    sobel_Y_1->insert(sobel_base_up);
    sobel_Y_2->insert(sobel_base_down);
}

void Edge_Detection::calc_gradient_magnitude(Matrix<int>& bitmap) {
    gradient_magnitude = std::make_unique<Matrix<float>>(bitmap.get_row(), bitmap.get_columns());
    auto gradient_X =
        std::make_unique<Matrix<float>>(bitmap.get_row(), bitmap.get_columns());
    auto gradient_Y =
        std::make_unique<Matrix<float>>(bitmap.get_row(), bitmap.get_columns());

    for (int i = 0; i < bitmap.get_row() * bitmap.get_columns(); ++i) {
        gradient_X->get_matrix()[i] = bitmap.get_matrix()[i];
        gradient_Y->get_matrix()[i] = bitmap.get_matrix()[i];
    }

    // finding the gradient for the x direction
    gradient_X->convolve(*sobel_X_1);
    gradient_X->convolve(*sobel_X_2);

    // finding gradient for the y direction
    gradient_Y->convolve(*sobel_Y_1);
    gradient_Y->convolve(*sobel_Y_2);

    for (int i = 0; i < bitmap.get_row() * bitmap.get_columns(); ++i) {
        gradient_magnitude->insert(
            hypot(gradient_X->get_matrix()[i], gradient_Y->get_matrix()[i]));
    }
}

void Edge_Detection::calc_gradient_direction(Matrix<int>& bitmap) {
    gradient_direction = std::make_unique<Matrix<int>>(bitmap.get_row(), bitmap.get_columns());
    auto gradient_X =
        std::make_unique<Matrix<float>>(bitmap.get_row(), bitmap.get_columns());
    auto gradient_Y =
        std::make_unique<Matrix<float>>(bitmap.get_row(), bitmap.get_columns());

    for (int i = 0; i < bitmap.get_row() * bitmap.get_columns(); ++i) {
        gradient_X->insert(bitmap.get_matrix()[i]);
        gradient_Y->insert(bitmap.get_matrix()[i]);
    }

    // finding the gradient for the x direction
    gradient_X->convolve(*sobel_X_1);
    gradient_X->convolve(*sobel_X_2);

    // finding gradient for the y direction
    gradient_Y->convolve(*sobel_Y_1);
    gradient_Y->convolve(*sobel_Y_2);

    int theta;
    for (int i = 0; i < bitmap.get_row() * bitmap.get_columns(); ++i) {
        theta = round(atan2((gradient_Y->get_matrix())[i], (gradient_X->get_matrix())[i]) * 180 / M_PI);
        if (theta >= 0 && theta <= 22.5)
            gradient_direction->insert(0);
        else if (theta >= 22.5 && theta <= 67.5)
            gradient_direction->insert(45);
        else if (theta > 67.5 && theta <= 112.5)
            gradient_direction->insert(90);
        else if (theta > 112.5 && theta <= 157.5)
            gradient_direction->insert(135);
        else if (theta > 157.5 && theta <= 180)
            gradient_direction->insert(0);
        else
            gradient_direction->insert(0);
    }
}

void Edge_Detection::lower_bound_cut_off_suppression() {
    auto calculated_G = std::make_unique<Matrix<float>>(
        gradient_magnitude->get_row(), gradient_magnitude->get_columns());
    *calculated_G = *gradient_magnitude;

    int columns = gradient_magnitude->get_columns();

    int plus_row    = 1;
    int plus_columns = 1;
    calculated_G->pad_vector(plus_row, plus_columns, 0);

    // refer to the Moore neighborhood to understand the orientation
    for (int i = plus_row; i < calculated_G->get_row() - plus_row; ++i) {
        for (int j = plus_columns; j < calculated_G->get_columns() - plus_columns; ++j) {
            auto current_value = (*calculated_G)[calculated_G->get_columns() * i + j];
            switch ((*gradient_direction)
                        .get_matrix()[columns * (i - plus_row) + (j - plus_columns)]) {
                case 0:    // check EAST and WEST
                    if (current_value > (*calculated_G)[calculated_G->get_columns() * i + j + 1] && current_value > (*calculated_G)[calculated_G->get_columns() * i + j - 1])
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = 0;
                    break;
                case 45:   // check NORTH-EAST and SOUTH-WEST
                    if (current_value > (*calculated_G)[calculated_G->get_columns() * (i - 1) + j + 1] && current_value > (*calculated_G)[calculated_G->get_columns() * (i + 1) + j - 1])
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = 0;
                    break;
                case 90:   // check NORTH and SOUTH
                    if (current_value > (*calculated_G)[calculated_G->get_columns() * (i - 1) + j] && current_value > (*calculated_G)[calculated_G->get_columns() * (i + 1) + j])
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = 0;
                    break;
                case 135:  // check NORTH-WEST and SOUTH-EAST
                    if (current_value > (*calculated_G)[calculated_G->get_columns() * (i - 1) + j - 1] && current_value > (*calculated_G)[calculated_G->get_columns() * (i + 1) + j + 1])
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = 0;
                    break;
                default:
                    (*gradient_magnitude)[columns * ( i - plus_row) + (j - plus_columns)] = current_value;
                    break;
            }
        }
    }
}

void Edge_Detection::lower_thresholding() const{
    for (int i = 0; i < gradient_magnitude->get_row() * gradient_magnitude->get_columns(); ++i) {
        if ((*gradient_magnitude)[i] < low_threshold)
            gradient_magnitude->get_matrix()[i] = 0;
    }
}

void Edge_Detection::edge_tracking_by_hysteresis() const {
    int row = gradient_magnitude->get_row();
    int columns = gradient_magnitude->get_columns();
    auto pad_gradient = std::make_unique<Matrix<float>>(row, columns);

    *pad_gradient = *gradient_magnitude;
    pad_gradient->pad_vector(1, 1, 0);
    for (int i = 1; i < pad_gradient->get_row() - 1 ; ++i) {
        for (int j = 1; j < pad_gradient->get_columns() - 1; ++j) {
            // means that we are dealing with a weak-edge pixel
            if ((*gradient_magnitude)[columns * (i - 1) + (j - 1)] < high_threshold) {
                // check in order:
                // EAST - WEST - NORTH - SOUTH - NORTH-EAST - SOUTH-WEST - NORTH-WEST - SOUTH-EAST
                if ((*pad_gradient)[pad_gradient->get_columns() * i + j + 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * i + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i - 1) + j] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i + 1) + j] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i - 1) + j + 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i + 1) + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i - 1) + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->get_columns() * (i + 1) + j + 1] > high_threshold)
                {
                    (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = (*pad_gradient)[pad_gradient->get_columns() * i + j];
                } else {
                    (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = 0;
                }
            }else{
                (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = (*pad_gradient)[pad_gradient->get_columns() * i + j];
            }
        }
    }
}

void Edge_Detection::apply(Image& img) {

    // smooth the image with a gaussian filter to reduce noise
    Gaussian_Blur blurring_filter(2);
    blurring_filter.apply(img);

    auto gray_scale_bitmap = img.get_gray_scale_bitmap();

    // compute the gradient magnitude
    calc_gradient_magnitude(*gray_scale_bitmap);

    // compute gradient direction angle
    calc_gradient_direction(*gray_scale_bitmap);

    lower_bound_cut_off_suppression();

    lower_thresholding();

    // now the thinned gradient_magnitude bitmap is left with only the pixels
    // that are considered weak or strong edge. In the last step Edge tracking
    // by hysteresis will be applied to leave only the weak edges that are
    // connected to strong edges

    edge_tracking_by_hysteresis();

    img.get_bitmap_R()->insert_with_round(*gradient_magnitude);
    img.get_bitmap_G()->insert_with_round(*gradient_magnitude);
    img.get_bitmap_B()->insert_with_round(*gradient_magnitude);
}