//
// Created by Alberto Cardini on 01/08/24.
//

#include "Image.hpp"

void Image::load_bitmap(std::ifstream& source) {
    int pixel = 0;
    if (type == "P2") {
        type = "P3";
        for (int i = 0; i < height * width; ++i) {
            source >> pixel;
            try {
                bitmap_R->insert(check_channel_value(pixel));
                bitmap_G->insert(check_channel_value(pixel));
                bitmap_B->insert(check_channel_value(pixel));
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
                bitmap_R->insert(check_channel_value(red));
                bitmap_G->insert(check_channel_value(green));
                bitmap_B->insert(check_channel_value(blue));
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
        input >> channel_range;

        bitmap_R = std::make_shared<Matrix<int>>(height, width);
        bitmap_G = std::make_shared<Matrix<int>>(height, width);
        bitmap_B = std::make_shared<Matrix<int>>(height, width);
        load_bitmap(input);

        input.close();
    } else {
        throw std::ifstream::failure("File not found or not readable");
    }
}

std::unique_ptr<Matrix<int>> Image::get_gray_scale_bitmap() {
    auto bitmap = std::make_unique<Matrix<int>>(height, width);
    for (int i = 0; i < height * width; ++i) {
        try {
            int pixel = R_COEF * (*bitmap_R)[i] + G_COEF * (*bitmap_G)[i] +
                        B_COEF * (*bitmap_B)[i];
            bitmap->insert(check_channel_value(pixel));
        } catch (const std::logic_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return bitmap;
}

void Image::save_gray_scale(const std::string& new_path) {
    Matrix<int> bitmap(height, width);
    if (new_path.find(".pgm") != std::string::npos) {
        std::ofstream new_image;
        std::string P2 = "P2";
        new_image.open(new_path.c_str());
        if (new_image.is_open()) {
            std::string charge_data = P2 + "\n" +
                                     std::to_string(width) + " " +
                                     std::to_string(height) + "\n" +
                                     std::to_string(channel_range) + "\n";
            for (int i = 0; i < height * width; ++i) {
                try {
                    // compute a weighted average of the RGB channels because
                    // the human brain reacts differently to RGB. Eyes are most
                    // sensitive to green light, less sensitive to red light,
                    // and the least sensitive to blue light.
                    int pixel = R_COEF * (*bitmap_R)[i] +
                                G_COEF * (*bitmap_G)[i] +
                                B_COEF * (*bitmap_B)[i];
                    charge_data +=
                        std::to_string(check_channel_value(pixel)) + "\n";
                } catch (const std::logic_error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            new_image << charge_data;
            new_image.close();
        }
    }
}

void Image::save(const std::string& path) {
    output.open(path.c_str());
    if (output.is_open()) {
        std::string charge_data = type + "\n" + std::to_string(width) + " " +
                                 std::to_string(height) + "\n" +
                                 std::to_string(channel_range) + "\n";

        for (int i = 0; i < height * width; ++i) {
            charge_data +=
                std::to_string(check_channel_value((*bitmap_R)[i])) + " " +
                std::to_string(check_channel_value((*bitmap_G)[i])) + " " +
                std::to_string(check_channel_value((*bitmap_B)[i])) + "\n";
        }
        output << charge_data;
        output.close();
    }
}

int Image::check_channel_value(int& value) {
    int fixed_value;
    if (value <= 255 && value >= 0) fixed_value = value;
    else if (value < 0) {
        value      = 0;
        fixed_value = 0;
    } else {
        value      = 255;
        fixed_value = 255;
    }
    return fixed_value;
}


