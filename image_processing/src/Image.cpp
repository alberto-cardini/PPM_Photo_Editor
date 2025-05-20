//
// Created by Alberto Cardini on 01/08/24.
//

#include "Image.hpp"
#include "matplot/matplot.h"

void Image::load_bitmap(std::ifstream &source) {
    uint16_t pixel = 0;
    if (type == "P2") {
        type = "P3";
        for (int i = 0; i < height * width; ++i) {
            source >> pixel;
            try {
                bitmap_R->insert(check_channel_value(pixel));
                bitmap_G->insert(check_channel_value(pixel));
                bitmap_B->insert(check_channel_value(pixel));
            } catch (const std::logic_error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } else if (type == "P3") {
        uint16_t red, green, blue;
        for (int i = 0; i < height * width; ++i) {
            source >> red;
            source >> green;
            source >> blue;
            try {
                bitmap_R->insert(check_channel_value(red));
                bitmap_G->insert(check_channel_value(green));
                bitmap_B->insert(check_channel_value(blue));
            } catch (const std::logic_error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

Image::Image(const std::string &path) {
    std::ifstream input;
    input.open(path.c_str());
    if (input.is_open()) {
        input >> type;
        input >> width;
        input >> height;
        input >> channel_range;

        bitmap_R = std::make_shared<Matrix<uint8_t>>(height, width);
        bitmap_G = std::make_shared<Matrix<uint8_t>>(height, width);
        bitmap_B = std::make_shared<Matrix<uint8_t>>(height, width);
        load_bitmap(input);

        input.close();
    } else {
        throw std::ifstream::failure("File not found or not readable");
    }
}

std::unique_ptr<Matrix<uint8_t>> Image::get_gray_scale_bitmap() {
    auto bitmap = std::make_unique<Matrix<uint8_t>>(height, width);
    for (int i = 0; i < height * width; ++i) {
        try {
            uint16_t pixel = R_COEF * (*bitmap_R)[i] + G_COEF * (*bitmap_G)[i] + B_COEF * (*bitmap_B)[i];
            bitmap->insert(check_channel_value(pixel));
        } catch (const std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return bitmap;
}

void Image::save_gray_scale(const std::string &new_path) {
    Matrix<float> bitmap(height, width);
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
                    // sensitive to green-light, less sensitive to red light,
                    // and the least sensitive to blue light.
                    uint16_t pixel = R_COEF * (*bitmap_R)[i] + G_COEF * (*bitmap_G)[i] + B_COEF * (*bitmap_B)[i];
                    charge_data += std::to_string(check_channel_value(pixel)) + "\n";
                } catch (const std::logic_error &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            new_image << charge_data;
            new_image.close();
        }
    }
}

void Image::save(const std::string &path) {
    output.open(path.c_str());
    if (output.is_open()) {
        std::string charge_data = type + "\n" + std::to_string(width) + " " +
                                  std::to_string(height) + "\n" +
                                  std::to_string(channel_range) + "\n";

        for (int i = 0; i < height * width; ++i) {
            charge_data +=
                    std::to_string((*bitmap_R)[i]) + " " +
                    std::to_string((*bitmap_G)[i]) + " " +
                    std::to_string((*bitmap_B)[i]) + "\n";
        }
        output << charge_data;
        output.close();
    } else {
        std::cout << path << "Image could not be saved" << std::endl;
    }
}

void Image::show_histogram() {

    std::string Xlabel = "Intensity";
    std::string Ylabel = "N. of Pixels";
    matplot::xlabel(Xlabel);
    matplot::ylabel(Ylabel);

    auto a = matplot::histogram::binning_algorithm::automatic;

    matplot::subplot(3,1,0);
    auto h1 = matplot::hist(bitmap_R->get_matrix(),a);
    h1->face_color("r");

    matplot::subplot(3,1,1);
    auto h2 = matplot::hist(bitmap_B->get_matrix(),a);
    h2->face_color("g");

    matplot::subplot(3,1,2);
    auto h3 = matplot::hist(bitmap_G->get_matrix(),a);
    h3->face_color("b");

    matplot::show();
}

uint8_t Image::check_channel_value(uint16_t &value) {
    uint8_t fixed_value;
    if (value <= 255)
        fixed_value = value;
    else {
        fixed_value = 255;
    }
    return fixed_value;
}


