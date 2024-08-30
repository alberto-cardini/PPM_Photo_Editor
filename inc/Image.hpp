//
// Created by Alberto Cardini on 01/08/24.
//

#ifndef PPM_PHOTO_EDITOR_IMAGE_HPP
#define PPM_PHOTO_EDITOR_IMAGE_HPP

#include <fstream>
#include <iostream>
#include <memory>

#include "Matrix.hpp"

class Image {
public:
    Image(const std::string& path);

    ~Image() { output.close(); };

    [[nodiscard]] std::string    getType() const { return type; }
    [[nodiscard]] auto           getBitmap_R() { return bitmap_R; }
    [[nodiscard]] auto           getBitmap_G() { return bitmap_G; }
    [[nodiscard]] auto           getBitmap_B() { return bitmap_B; }

    [[nodiscard]] int            getHeight() const { return height; }
    [[nodiscard]] int            getWidth() const { return width; }

    void                         save(const std::string& path);
    void                         saveGrayScale(const std::string& new_path);
    std::unique_ptr<Matrix<int>> getGrayScaleBitmap();

private:
    void                         loadBitmap(std::ifstream& source);
    int                          checkChannelValue(int& value) const;

    std::string                  type;

    std::shared_ptr<Matrix<int>> bitmap_R;
    std::shared_ptr<Matrix<int>> bitmap_G;
    std::shared_ptr<Matrix<int>> bitmap_B;

    std::ofstream                output;

    int                          height{0};
    int                          width{0};
    int                          channelRange{0};

    const float                  R_COEF = 0.2989;
    const float                  G_COEF = 0.5870;
    const float                  B_COEF = 0.1140;
};

#endif  // PPM_PHOTO_EDITOR_IMAGE_HPP
