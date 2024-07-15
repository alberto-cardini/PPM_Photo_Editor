//
// Created by Alberto Cardini on 12/06/24.
//

#ifndef MINIPHOTOEDITOR_IMAGE_HPP
#define MINIPHOTOEDITOR_IMAGE_HPP

#include <fstream>
#include <iostream>
#include <memory>

#include "Matrix.hpp"

class RGB_image {
public:
    RGB_image(const std::string& input_path, const std::string& output_path);

    ~RGB_image() { output.close(); };

    [[nodiscard]] std::string getType() const { return type; }
    [[nodiscard]] auto        getBitmap_R() { return bitmap_R; }
    [[nodiscard]] auto        getBitmap_G() { return bitmap_G; }
    [[nodiscard]] auto        getBitmap_B() { return bitmap_B; }

    [[nodiscard]] auto&       getInputPath() const { return input_path; }
    [[nodiscard]] auto&       getOutputPath() const { return output_path; }
    [[nodiscard]] int         getHeight() const { return height; }
    [[nodiscard]] int         getWidth() const { return width; }

    void                      setHeight(int h) { height = h; }
    void                      setWidth(int w) { width = w; }

    void                      save();

private:
    void                         loadBitmap(std::ifstream& source);
    int                          checkChannelValue(int& value) const;

    std::string                  type;
    std::string                  output_path;
    std::string                  input_path;

    std::shared_ptr<Matrix<int>> bitmap_R;
    std::shared_ptr<Matrix<int>> bitmap_G;
    std::shared_ptr<Matrix<int>> bitmap_B;

    std::ofstream                output;

    int                          height{0};
    int                          width{0};
    int                          channelRange{0};
};

#endif  // MINIPHOTOEDITOR_IMAGE_HPP
