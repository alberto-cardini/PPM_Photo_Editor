//
// Created by Alberto Cardini on 15/07/24.
//

#include "Gray_Scale_image.hpp"

Gray_Scale_image::Gray_Scale_image(const std::string& input_path,
                                   const std::string& path)
    : input_path(input_path), output_path(path) {
    initialize();
}

Gray_Scale_image::Gray_Scale_image(RGB_image& src) {
    input_path  = src.getInputPath();
    output_path.assign(src.getOutputPath());
    // delete the original extension and replace it with .pgm
    output_path.pop_back();
    output_path.pop_back();
    output_path.pop_back();
    output_path.append("pgm");
    initialize();
}

void Gray_Scale_image::loadBitmap(std::ifstream& source) {
    if (input_path.find(".pgm") != std::string::npos) {
        int pixel = 0;
        for (int i = 0; i < height * width; ++i) {
            source >> pixel;
            try {
                bitmap->insert(checkChannelValue(pixel));
            } catch (const std::logic_error& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } else if (input_path.find(".ppm") != std::string::npos) {
        int red, green, blue;
        int pixel = 0;
        for (int i = 0; i < height * width; ++i) {
            source >> red;
            source >> green;
            source >> blue;
            try {
                // compute a weighted average of the RGB channels because the
                // human brain reacts differently to RGB. Eyes are most
                // sensitive to green light, less sensitive to red light, and
                // the least sensitive to blue light.
                pixel = R_COEF * checkChannelValue(red) +
                        G_COEF * checkChannelValue(green) +
                        B_COEF * checkChannelValue(blue);
                bitmap->insert(checkChannelValue(pixel));
            } catch (const std::logic_error& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void Gray_Scale_image::initialize() {
    std::ifstream input;
    input.open(input_path.c_str());
    if (input.is_open()) {
        input >> type;
        input >> width;
        input >> height;
        input >> gray_range;

        // if the condition is verified it means that the client is trying to
        // convert a .ppm in a .pgm. Therefore, the type is changed to P2
        if (input_path.find(".ppm") != std::string::npos && output_path.find(".pgm") != std::string::npos)
            type = "P2";

        output.open(output_path.c_str());
        if (output.is_open()) {
            std::string chargeData = type + "\n" + std::to_string(width) + " " +
                                     std::to_string(height) + "\n" +
                                     std::to_string(gray_range) + "\n";
            output << chargeData;
            bitmap = std::make_shared<Matrix<int>>(height, width);
            loadBitmap(input);

            output.close();
        } else
            throw std::ifstream::failure("File not found or not readable");
    }
}

void Gray_Scale_image::save() {
    output.open(output_path.c_str());
    if (output.is_open()) {
        std::string chargeData = type + "\n" + std::to_string(width) + " " +
                                 std::to_string(height) + "\n" +
                                 std::to_string(gray_range) + "\n";

        for (int i = 0; i < height * width; ++i) {
            chargeData +=
                std::to_string(checkChannelValue((*bitmap)[i])) + "\n";
        }
        output << chargeData;
        output.close();
    }
}

int Gray_Scale_image::checkChannelValue(int& value) const {
    int fixedValue = value;
    if (value <= 255 && value >= 0) fixedValue = value;
    else if (value < 0) {
        value      = 0;
        fixedValue = 0;
    } else {
        value      = 255;
        fixedValue = 255;
    }
    return fixedValue;
}

auto Gray_Scale_image::RGB_to_gray_scale(RGB_image& src) {
    auto gray_scale = std::make_unique<Gray_Scale_image>(src);
    return gray_scale;
}
