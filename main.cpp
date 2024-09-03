//
// Created by Alberto Cardini on 20/05/24.
//
#include <iostream>

#include "Edge_Detection.hpp"
#include "Image.hpp"

int main() {

    Image i1("test_asset/sunflower.ppm");
    Edge_Detection filter(40,20);

    Image i2("test_asset/sunflower.ppm");
    Gaussian_Blur blur_filter(7);

    filter.apply(i1);
    i1.save("output/sunflower_only_edges.ppm");

    blur_filter.apply(i2);
    i2.save("output/sunflower_blurred.ppm");

    return 0;
}