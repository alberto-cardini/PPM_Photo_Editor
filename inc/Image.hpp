//
// Created by Alberto Cardini on 12/06/24.
//

#ifndef MINIPHOTOEDITOR_IMAGE_HPP
#define MINIPHOTOEDITOR_IMAGE_HPP

#include <fstream>
#include <iostream>
#include <memory>

#include "Matrix.hpp"

class Image {
public:
    Image(const std::string& input_path, const std::string& output_path);

    ~Image() { output.close(); };

    [[nodiscard]] std::string getType() const { return type; }
    [[nodiscard]] auto&       getBitmap_R() { return bitmap_R; }
    [[nodiscard]] auto&       getBitmap_G() { return bitmap_G; }
    [[nodiscard]] auto&       getBitmap_B() { return bitmap_B; }

    [[nodiscard]] auto&       getBitmap_RRAW() { return *bitmap_R; }
    [[nodiscard]] auto&       getBitmap_GRAW() { return *bitmap_G; }
    [[nodiscard]] auto&       getBitmap_BRAW() { return *bitmap_B; }

    [[nodiscard]] auto&       getFile() const { return output; }
    [[nodiscard]] int         getHeight() const { return height; }
    [[nodiscard]] int         getWidth() const { return width; }

    void                      setHeight(int h) { height = h; }
    void                      setWidth(int w) { width = w; }

    void                      save();

private:
    void                         loadBitmap(std::ifstream& source);
    int                          checkChannelValue(int& value) const;

    std::string                  type;
    std::string                  path;

    std::shared_ptr<Matrix<int>> bitmap_R;
    std::shared_ptr<Matrix<int>> bitmap_G;
    std::shared_ptr<Matrix<int>> bitmap_B;

    std::ofstream                output;

    int                          height{0};
    int                          width{0};
    int                          channelRange{0};
};

#endif  // MINIPHOTOEDITOR_IMAGE_HPP
