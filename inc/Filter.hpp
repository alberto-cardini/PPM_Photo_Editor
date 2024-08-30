//
// Created by Alberto Cardini on 29/06/24.
//

#ifndef MINIPHOTOEDITOR_FILTER_HPP
#define MINIPHOTOEDITOR_FILTER_HPP
#include <cmath>
#include <iostream>
#include <memory>

#include "Image.hpp"

class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(Image& img) = 0;
};

#endif  // MINIPHOTOEDITOR_FILTER_HPP
