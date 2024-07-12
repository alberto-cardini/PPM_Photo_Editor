//
// Created by Alberto Cardini on 11/07/24.
//

#include "EdgeDetection.hpp"
EdgeDetection::EdgeDetection() {
    sobelKernelY = std::make_unique<Matrix<float>>(3,3);
    std::vector<float> baseY = {1, 0, -1,
                                2, 0, -2,
                                1, 0, -1};
    sobelKernelY->insert(baseY);

    sobelKernelX = std::make_unique<Matrix<float>>(3,3);
    std::vector<float> base2 = {1, 2, 1,
                                0, 0, 0,
                                -1, -2, -1};
    sobelKernelY->insert(base2);
}

void EdgeDetection::enhance(Image& img) {
    auto bitmap_R = img.getBitmap_R();
    auto bitmap_G = img.getBitmap_G();
    auto bitmap_B = img.getBitmap_B();
    for (int i = 0; i < bitmap_R->getRow() * bitmap_R->getColumns(); ++i) {
        if ( (*bitmap_R)[i] > 50 || (*bitmap_G)[i] > 50 || (*bitmap_B)[i] > 50 ) {
            (*bitmap_R)[i] = 255;
            (*bitmap_G)[i] = 255;
            (*bitmap_B)[i] = 255;
        }else if((*bitmap_R)[i] < 50 && (*bitmap_G)[i] < 50 && (*bitmap_B)[i] < 50) {
            (*bitmap_R)[i] = 0;
            (*bitmap_G)[i] = 0;
            (*bitmap_B)[i] = 0;
        }
    }
}

void EdgeDetection::apply(Image &img) {
    GaussianBlur blurringFilter(4);
    blurringFilter.apply(img);

    img.getBitmap_R()->convolve(*sobelKernelY);
    img.getBitmap_G()->convolve(*sobelKernelY);
    img.getBitmap_B()->convolve(*sobelKernelY);
}