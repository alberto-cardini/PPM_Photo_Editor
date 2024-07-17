//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_FILTER_HPP
#define MINIPHOTOEDITOR_FILTER_HPP
#include <cmath>
#include <iostream>
#include <memory>

#include "Gray_Scale_image.hpp"
#include "RGB_image.hpp"

class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(RGB_image& img) = 0;
    virtual void apply(Gray_Scale_image& img) = 0;
};

#endif  // MINIPHOTOEDITOR_FILTER_HPP
