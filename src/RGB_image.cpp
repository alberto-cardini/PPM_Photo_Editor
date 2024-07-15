//
// Created by Alberto Cardini on 12/06/24.
//

#include "RGB_image.hpp"

void RGB_image::loadBitmap(std::ifstream& source) {
    int red, green, blue;
    for (int i = 0; i < height * width; ++i) {
        source >> red;
        source >> green;
        source >> blue;
        try {
            bitmap_R->insert(checkChannelValue(red));
            bitmap_G->insert(checkChannelValue(green));
            bitmap_B->insert(checkChannelValue(blue));
        } catch (const std::logic_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

RGB_image::RGB_image(const std::string& input_path, const std::string& path)
    : input_path(input_path), output_path(path) {
    std::ifstream input;
    input.open(input_path.c_str());
    if (input.is_open()) {
        input >> type;
        input >> width;
        input >> height;
        input >> channelRange;

        output.open(output_path.c_str());
        if (output.is_open()) {
            std::string chargeData = type + "\n" +
                                     std::to_string(width) + " " +
                                     std::to_string(height) + "\n" +
                                     std::to_string(channelRange) + "\n";
            output << chargeData;

            bitmap_R = std::make_shared<Matrix<int>>(height, width);
            bitmap_G = std::make_shared<Matrix<int>>(height, width);
            bitmap_B = std::make_shared<Matrix<int>>(height, width);
            loadBitmap(input);

            output.close();
        }
        input.close();
    } else
        throw std::ifstream::failure("File not found or not readable");
}

void RGB_image::save() {
    output.open(output_path.c_str());
    if (output.is_open()) {
        std::string chargeData = type + "\n" + std::to_string(width) + " " +
                                 std::to_string(height) + "\n" +
                                 std::to_string(channelRange) + "\n";

        for (int i = 0; i < height * width; ++i) {
            chargeData +=
                std::to_string(checkChannelValue((*bitmap_R)[i])) + " " +
                std::to_string(checkChannelValue((*bitmap_G)[i])) + " " +
                std::to_string(checkChannelValue((*bitmap_B)[i])) + "\n";
        }
        output << chargeData;
        output.close();
    }
}

int RGB_image::checkChannelValue(int& value) const {
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
