//
// Created by Alberto Cardini on 12/06/24.
//

#ifndef MINIPHOTOEDITOR_IMAGE_HPP
#define MINIPHOTOEDITOR_IMAGE_HPP

#include <fstream>
#include <iostream>

#include "Matrix.hpp"

class Image {
public:
    Image(const std::string& input_path, const std::string& output_path);

    ~Image() { output.close(); };

    [[nodiscard]] std::string getType() const { return type; }
    [[nodiscard]] auto&       getBitmap() const { return bitmap; }
    [[nodiscard]] auto&       getFile() const { return output; }
    [[nodiscard]] int         getHeight() const { return height; }
    [[nodiscard]] int         getWidth() const { return width; }

    void                      setHeight(int h) { height = h; }
    void                      setWidth(int w) { width = w; }
    Pixel                     getBitmapAverage() const;

    void                      save();

private:
    void                           loadBitmap(std::ifstream& source);

    std::string                    type;

    std::shared_ptr<Matrix<Pixel>> bitmap;
    std::ofstream                  output;

    int                            height{0};
    int                            width{0};
    int                            channelRange{0};
};

#endif  // MINIPHOTOEDITOR_IMAGE_HPP
