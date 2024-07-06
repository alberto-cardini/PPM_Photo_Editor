//
// Created by Alberto Cardini on 03/07/24.
//

#include "Pixel.hpp"
#include <iostream>

Pixel::Pixel(int red, int green, int blue) {
    pixelValueCheck(red, green, blue);
}

void Pixel::setPixel(const Pixel& src) {
    R = src.R;
    B = src.B;
    G = src.G;
}

void Pixel::setPixel(int red, int green, int blue) {
    pixelValueCheck(red, green, blue);
}

void Pixel::pixelValueCheck(int red, int green, int blue) {
    if ( red <= 255 && red >= 0) R = red;
    else if ( red < 0 ) R = 0;
    else R = 255;

    if ( green <= 255 && green >= 0) G = green;
    else if ( red < 0 ) G = 0;
    else G = 255;

    if ( blue <= 255 && blue >= 0) B = blue;
    else if ( red < 0 ) B = 0;
    else B = 255;
}

int Pixel::getPixelChannel(PixelChannel channel) const {
    switch (channel) {
        case PixelChannel::RED  : return R;
        case PixelChannel::BLUE : return B;
        case PixelChannel::GREEN: return G;
        default                 : return R;
    }
}

Pixel& Pixel::operator/(int scalar) {
    pixelValueCheck(R / scalar, G / scalar, B / scalar);
    return *this;
}

Pixel& Pixel::operator=(int scalar){
    pixelValueCheck(scalar, scalar, scalar);
    return *this;
}

Pixel& Pixel::operator+(const Pixel& right){
    pixelValueCheck(R + right.R, G + right.G, B + right.B);
    return *this;
}

Pixel& Pixel::operator%(int scalar){
    pixelValueCheck(R % scalar, G % scalar, B % scalar);
    return *this;
}