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

    [[nodiscard]] std::string    get_type() const { return type; }
    [[nodiscard]] int            get_range() const { return channel_range; }
    [[nodiscard]] auto           get_bitmap_R() { return bitmap_R; }
    [[nodiscard]] auto           get_bitmap_G() { return bitmap_G; }
    [[nodiscard]] auto           get_bitmap_B() { return bitmap_B; }

    [[nodiscard]] int            get_height() const { return height; }
    [[nodiscard]] int            get_width() const { return width; }

    void                         save(const std::string& path);
    void                         save_gray_scale(const std::string& new_path);
    static int                   check_channel_value(int& value);
    std::unique_ptr<Matrix<int>> get_gray_scale_bitmap();

private:
    void                         load_bitmap(std::ifstream& source);

    std::string                  type;

    std::shared_ptr<Matrix<int>> bitmap_R;
    std::shared_ptr<Matrix<int>> bitmap_G;
    std::shared_ptr<Matrix<int>> bitmap_B;

    std::ofstream                output;

    int                          height{0};
    int                          width{0};
    int                          channel_range{0};

    const float                  R_COEF = 0.2989;
    const float                  G_COEF = 0.5870;
    const float                  B_COEF = 0.1140;
};

#endif  // PPM_PHOTO_EDITOR_IMAGE_HPP
