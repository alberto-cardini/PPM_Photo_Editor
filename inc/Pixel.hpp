//
// Created by Alberto Cardini on 03/07/24.
//

#ifndef MINIPHOTOEDITOR_PIXEL_HPP
#define MINIPHOTOEDITOR_PIXEL_HPP

enum PixelChannel { RED, GREEN, BLUE };

class Pixel {
private:
    int R {0}, G {0}, B {0};

    void pixelValueCheck(int red, int green, int blue);

public:
    Pixel() = default;
    Pixel(const Pixel& src) { R = src.R; G = src.G; B = src.B; };
    Pixel(int red, int green, int blue);
    void setPixel(const Pixel& src);
    void setPixel(int red, int green, int blue);
    int  getPixelChannel(PixelChannel channel) const;

    Pixel& operator/(int scalar);
    Pixel& operator=(int scalar);
    Pixel& operator=(const Pixel& src) = default;

    Pixel& operator%(int scalar);

    Pixel& operator+(int scalar);
    Pixel& operator*(int scalar);
    Pixel& operator-(int scalar);

    Pixel& operator/(const Pixel& right);
    Pixel& operator+(const Pixel& right);
    Pixel& operator*(const Pixel& right);
    Pixel& operator-(const Pixel& right);
};


#endif  // MINIPHOTOEDITOR_PIXEL_HPP
