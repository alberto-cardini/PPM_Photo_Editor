//
// Created by Alberto Cardini on 11/07/24.
//

#include "EdgeDetection.hpp"
EdgeDetection::EdgeDetection(float h, float l) : high_threshold(h), low_threshold(l) {
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

void EdgeDetection::calc_gradient_magnitude(Matrix<int>& bitmap) {
    gradient_magnitude = std::make_unique<Matrix<float>>(bitmap.getRow(), bitmap.getColumns());
    auto gradient_X =
        std::make_unique<Matrix<float>>(bitmap.getRow(), bitmap.getColumns());
    auto gradient_Y =
        std::make_unique<Matrix<float>>(bitmap.getRow(), bitmap.getColumns());

    for (int i = 0; i < bitmap.getRow() * bitmap.getColumns(); ++i) {
        gradient_X->getMatrix()[i] = bitmap.getMatrix()[i];
        gradient_Y->getMatrix()[i] = bitmap.getMatrix()[i];
    }

    // finding the gradient for the x direction
    gradient_X->convolve(*sobel_X_1);
    gradient_X->convolve(*sobel_X_2);

    // finding gradient for the y direction
    gradient_Y->convolve(*sobel_Y_1);
    gradient_Y->convolve(*sobel_Y_2);

    for (int i = 0; i < bitmap.getRow() * bitmap.getColumns(); ++i) {
        gradient_magnitude->insert(
            hypot(gradient_X->getMatrix()[i], gradient_Y->getMatrix()[i]));
    }
}

void EdgeDetection::calc_gradient_direction(Matrix<int>& bitmap) {
    gradient_direction = std::make_unique<Matrix<int>>(bitmap.getRow(), bitmap.getColumns());
    auto gradient_X =
        std::make_unique<Matrix<float>>(bitmap.getRow(), bitmap.getColumns());
    auto gradient_Y =
        std::make_unique<Matrix<float>>(bitmap.getRow(), bitmap.getColumns());

    for (int i = 0; i < bitmap.getRow() * bitmap.getColumns(); ++i) {
        gradient_X->insert(bitmap.getMatrix()[i]);
        gradient_Y->insert(bitmap.getMatrix()[i]);
    }

    // finding the gradient for the x direction
    gradient_X->convolve(*sobel_X_1);
    gradient_X->convolve(*sobel_X_2);

    // finding gradient for the y direction
    gradient_Y->convolve(*sobel_Y_1);
    gradient_Y->convolve(*sobel_Y_2);

    int theta;
    for (int i = 0; i < bitmap.getRow() * bitmap.getColumns(); ++i) {
        theta = round(atan2((gradient_Y->getMatrix())[i], (gradient_X->getMatrix())[i]) * 180 / M_PI);
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

void EdgeDetection::lower_bound_cut_off_suppression() {
    auto calculated_G = std::make_unique<Matrix<float>>(gradient_magnitude->getRow(), gradient_magnitude->getColumns());
    *calculated_G = *gradient_magnitude;

    int columns = gradient_magnitude->getColumns();

    int plusRow = 1;
    int plusColumns = 1;
    calculated_G->padVector(plusRow,plusColumns,0);

    // refer to the Moore neighborhood to understand the orientation
    for (int i = plusRow; i < calculated_G->getRow() - plusRow; ++i) {
        for (int j = plusColumns; j < calculated_G->getColumns() - plusColumns; ++j) {
            auto current_value = (*calculated_G)[calculated_G->getColumns() * i + j];
            switch ((*gradient_direction).getMatrix()[columns * (i - plusRow) + (j - plusColumns)]) {
                case 0:    // check EAST and WEST
                    if (current_value > (*calculated_G)[calculated_G->getColumns() * i + j + 1] && current_value > (*calculated_G)[calculated_G->getColumns() * i + j - 1])
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = 0;
                    break;
                case 45:   // check NORTH-EAST and SOUTH-WEST
                    if (current_value > (*calculated_G)[calculated_G->getColumns() * (i - 1) + j + 1] && current_value > (*calculated_G)[calculated_G->getColumns() * (i + 1) + j - 1])
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = 0;
                    break;
                case 90:   // check NORTH and SOUTH
                    if (current_value > (*calculated_G)[calculated_G->getColumns() * (i - 1) + j] && current_value > (*calculated_G)[calculated_G->getColumns() * (i + 1) + j])
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = 0;
                    break;
                case 135:  // check NORTH-WEST and SOUTH-EAST
                    if (current_value > (*calculated_G)[calculated_G->getColumns() * (i - 1) + j - 1] && current_value > (*calculated_G)[calculated_G->getColumns() * (i + 1) + j + 1])
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = current_value;
                    else
                        (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = 0;
                    break;
                default:
                    (*gradient_magnitude)[columns * ( i - plusRow) + (j - plusColumns)] = current_value;
                    break;
            }
        }
    }
}

void EdgeDetection::lower_thresholding() const{
    for (int i = 0; i < gradient_magnitude->getRow() * gradient_magnitude->getColumns(); ++i) {
        if ((*gradient_magnitude)[i] < low_threshold)
            gradient_magnitude->getMatrix()[i] = 0;
    }
}

void EdgeDetection::edge_tracking_by_hysteresis() const {
    int row = gradient_magnitude->getRow();
    int columns = gradient_magnitude->getColumns();
    auto pad_gradient = std::make_unique<Matrix<float>>(row, columns);

    *pad_gradient = *gradient_magnitude;
    pad_gradient->padVector(1,1,0);
    for (int i = 1; i < pad_gradient->getRow() - 1 ; ++i) {
        for (int j = 1; j < pad_gradient->getColumns() - 1; ++j) {
            // means that we are dealing with a weak-edge pixel
            if ((*gradient_magnitude)[columns * (i - 1) + (j - 1)] < high_threshold) {
                // check in order:
                // EAST - WEST - NORTH - SOUTH - NORTH-EAST - SOUTH-WEST - NORTH-WEST - SOUTH-EAST
                if ((*pad_gradient)[pad_gradient->getColumns() * i + j + 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * i + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i - 1) + j] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i + 1) + j] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i - 1) + j + 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i + 1) + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i - 1) + j - 1] > high_threshold ||
                    (*pad_gradient)[pad_gradient->getColumns() * (i + 1) + j + 1] > high_threshold) {
                    (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = (*pad_gradient)[pad_gradient->getColumns() * i + j];
                } else {
                    (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = 0;
                }
            }else{
                (*gradient_magnitude)[columns * (i - 1) + (j - 1)] = (*pad_gradient)[pad_gradient->getColumns() * i + j];
            }
        }
    }
}

void EdgeDetection::apply(Image& img) {

    // smooth the image with a gaussian filter to reduce noise
    GaussianBlur blurringFilter(2);
    blurringFilter.apply(img);

    auto Gray_Scale_Bitmap = img.getGrayScaleBitmap();

    // compute the gradient magnitude
    calc_gradient_magnitude(*Gray_Scale_Bitmap);

    // compute gradient direction angle
    calc_gradient_direction(*Gray_Scale_Bitmap);

    lower_bound_cut_off_suppression();

    lower_thresholding();

    // now the thinned gradient_magnitude bitmap is left with only the pixels
    // that are considered weak or strong edge. In the last step Edge tracking
    // by hysteresis will be applied to leave only the weak edges that are
    // connected to strong edges

    edge_tracking_by_hysteresis();

    img.getBitmap_R()->insertWithRound(*gradient_magnitude);
    img.getBitmap_G()->insertWithRound(*gradient_magnitude);
    img.getBitmap_B()->insertWithRound(*gradient_magnitude);
}