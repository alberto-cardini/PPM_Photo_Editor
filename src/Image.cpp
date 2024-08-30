//
// Created by Alberto Cardini on 01/08/24.
//

#include "Image.hpp"

void Image::loadBitmap(std::ifstream& source) {
    int pixel = 0;
    if (type == "P2") {
        type = "P3";
        for (int i = 0; i < height * width; ++i) {
            source >> pixel;
            try {
                bitmap_R->insert(checkChannelValue(pixel));
                bitmap_G->insert(checkChannelValue(pixel));
                bitmap_B->insert(checkChannelValue(pixel));
            } catch (const std::logic_error& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } else if (type == "P3") {
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
}

Image::Image(const std::string& path) {
    std::ifstream input;
    input.open(path.c_str());
    if (input.is_open()) {
        input >> type;
        input >> width;
        input >> height;
        input >> channelRange;

        bitmap_R = std::make_shared<Matrix<int>>(height, width);
        bitmap_G = std::make_shared<Matrix<int>>(height, width);
        bitmap_B = std::make_shared<Matrix<int>>(height, width);
        loadBitmap(input);

        input.close();
    } else {
        throw std::ifstream::failure("File not found or not readable");
    }
}

std::unique_ptr<Matrix<int>> Image::getGrayScaleBitmap() {
    auto bitmap = std::make_unique<Matrix<int>>(height, width);
    for (int i = 0; i < height * width; ++i) {
        try {
            int pixel = R_COEF * (*bitmap_R)[i] + G_COEF * (*bitmap_G)[i] +
                        B_COEF * (*bitmap_B)[i];
            bitmap->insert(checkChannelValue(pixel));
        } catch (const std::logic_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return bitmap;
}

void Image::saveGrayScale(const std::string& new_path) {
    Matrix<int> bitmap(height, width);
    if (new_path.find(".pgm") != std::string::npos) {
        std::ofstream newImage;
        std::string P2 = "P2";
        newImage.open(new_path.c_str());
        if (newImage.is_open()) {
            std::string chargeData = P2 + "\n" +
                                     std::to_string(width) + " " +
                                     std::to_string(height) + "\n" +
                                     std::to_string(channelRange) + "\n";
            for (int i = 0; i < height * width; ++i) {
                try {
                    // compute a weighted average of the RGB channels because
                    // the human brain reacts differently to RGB. Eyes are most
                    // sensitive to green light, less sensitive to red light,
                    // and the least sensitive to blue light.
                    int pixel = R_COEF * (*bitmap_R)[i] +
                                G_COEF * (*bitmap_G)[i] +
                                B_COEF * (*bitmap_B)[i];
                    chargeData +=
                        std::to_string(checkChannelValue(pixel)) + "\n";
                } catch (const std::logic_error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            newImage << chargeData;
            newImage.close();
        }
    }
}

void Image::save(const std::string& path) {
    output.open(path.c_str());
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

int Image::checkChannelValue(int& value) const {
    int fixedValue;
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

