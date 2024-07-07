//
// Created by Alberto Cardini on 12/06/24.
//

#include "Image.hpp"

void Image::loadBitmap(std::ifstream& source) {
    int red, green, blue;
    while (!source.eof()) {
        source >> red;
        source >> green;
        source >> blue;
        try {
            Pixel newPixel(red, green, blue);
            bitmap_R->insertValue(newPixel.getPixelChannel(RED));
            bitmap_G->insertValue(newPixel.getPixelChannel(GREEN));
            bitmap_B->insertValue(newPixel.getPixelChannel(BLUE));
        } catch (const std::logic_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

Image::Image(const std::string& input_path, const std::string& path) : path(path) {
    std::ifstream input;
    input.open(input_path.c_str());
    if (input.is_open()) {
        input >> type;
        input >> width;
        input >> height;
        input >> channelRange;

        output.open(path.c_str());
        output << type << std::endl;
        output << width << " " << height << std::endl;
        output << channelRange << std::endl;

        //bitmap = std::make_shared<Matrix<Pixel>>(height, width);
        bitmap_R = std::make_shared<Matrix<int>>(height, width);
        bitmap_G = std::make_shared<Matrix<int>>(height, width);
        bitmap_B = std::make_shared<Matrix<int>>(height, width);
        loadBitmap(input);

        for (int i = 0; i < height * width; ++i) {
            output << (*bitmap_R)[i] << " ";
            output << (*bitmap_G)[i] << " ";
            output << (*bitmap_B)[i] << " "
                   << std::endl;
        }
        output.close();
        input.close();
    } else
        throw std::ifstream::failure("File not found or not readable");
}

void Image::save() {
    output.open(path.c_str());
    if (output.is_open()) {
        output << type << std::endl;
        output << width << " " << height << std::endl;
        output << channelRange << std::endl;
        for (int i = 0; i < height * width; ++i) {
            output << (*bitmap_R)[i] << " ";
            output << (*bitmap_G)[i] << " ";
            output << (*bitmap_B)[i] << " "
                   << std::endl;
        }
    }
    output.close();
}

