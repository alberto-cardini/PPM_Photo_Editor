//
// Created by Alberto Cardini on 20/05/24.
//
#include <iostream>
#include "EdgeDetection.hpp"
#include "Filter.hpp"
#include "RGB_image.hpp"
#include "Gray_Scale_image.hpp"

int main() {

    auto startLoad = std::chrono::system_clock::now();

    RGB_image i1("input/sunflower.ppm", "output/prova4.ppm");
    Gray_Scale_image i2("input/sunflower_gray_scale.pgm", "output/Edge7.pgm");

    auto endLoad = std::chrono::system_clock::now();
    float elapsedLoad = std::chrono::duration_cast<std::chrono::seconds>(endLoad-startLoad).count();
    printf("Time %.4fms\n", elapsedLoad);

    auto start = std::chrono::system_clock::now();

    EdgeDetection filter(30,60);
    filter.apply(i2);

    auto end = std::chrono::system_clock::now();
    float elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    printf("Time %.4fms\n", elapsed);


    auto startSave = std::chrono::system_clock::now();

    i2.save();
    i1.save();

    auto endSave = std::chrono::system_clock::now();
    float elapsedSave = std::chrono::duration_cast<std::chrono::seconds>(endSave-startSave).count();
    printf("Time %.4fms\n", elapsedSave);

    return 0;
}