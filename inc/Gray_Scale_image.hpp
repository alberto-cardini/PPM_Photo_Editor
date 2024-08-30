//
// Created by Alberto Cardini on 15/07/24.
//

#ifndef PPM_PHOTO_EDITOR_GRAY_SCALE_IMAGE_HPP
#define PPM_PHOTO_EDITOR_GRAY_SCALE_IMAGE_HPP
#include <fstream>
#include <iostream>
#include <memory>

#include "Matrix.hpp"
#include "RGB_image.hpp"

class Gray_Scale_image {
public:
    Gray_Scale_image(const std::string& input_path,
                     const std::string& output_path);
    explicit Gray_Scale_image(RGB_image& src);

    ~Gray_Scale_image() { output.close(); };
    [[nodiscard]] std::string getType() const { return type; }

    [[nodiscard]] auto        getBitmap(){ return bitmap; }
    [[nodiscard]] auto&       getInputPath() const{ return input_path; }
    [[nodiscard]] auto&       getOutputPath() const{ return output_path; }
    [[nodiscard]] int         getHeight() const { return height; }

    [[nodiscard]] int         getWidth() const { return width; }
    void                      setHeight(int h) { height = h; }

    void                      setWidth(int w) { width = w; }
    void                      save();

    auto                      RGB_to_gray_scale(RGB_image& src);
private:

    void loadBitmap(std::ifstream& source);
    int  checkChannelValue(int& value) const;
    void initialize();

    std::string                  type;
    std::string                  output_path;
    std::string                  input_path;

    std::shared_ptr<Matrix<int>> bitmap;

    std::ofstream                output;

    int                          height{0};
    int                          width{0};
    int                          gray_range{0};

    const float                  R_COEF = 0.2989;
    const float                  G_COEF = 0.5870;
    const float                  B_COEF = 0.1140;
};

#endif  // PPM_PHOTO_EDITOR_GRAY_SCALE_IMAGE_HPP
