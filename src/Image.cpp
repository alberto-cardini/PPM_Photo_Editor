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
            bitmap->insertValue(newPixel);
        } catch (const std::logic_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

Image::Image(const std::string& input_path, const std::string& path) {
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

        bitmap = std::make_shared<Matrix<Pixel>>(height, width);
        loadBitmap(input);

        for (int i = 0; i < height * width; ++i) {
            output << (*bitmap)[i].getPixelChannel(PixelChannel::RED) << " ";
            output << (*bitmap)[i].getPixelChannel(PixelChannel::GREEN) << " ";
            output << (*bitmap)[i].getPixelChannel(PixelChannel::BLUE)
                   << std::endl;
        }
        output.close();
        input.close();
    } else
        throw std::ifstream::failure("File not found or not readable");
}

void Image::save() {
    output.open("output/prima_prova.ppm");
    if (output.is_open()) {
        output << type << std::endl;
        output << width << " " << height << std::endl;
        output << channelRange << std::endl;
        for (int i = 0; i < height * width; ++i) {
            output << (*bitmap)[i].getPixelChannel(PixelChannel::RED) << " ";
            output << (*bitmap)[i].getPixelChannel(PixelChannel::GREEN) << " ";
            output << (*bitmap)[i].getPixelChannel(PixelChannel::BLUE)
                   << std::endl;
        }
    }
    output.close();
}

//Return the average color of the image (Arithmetic)
Pixel Image::getBitmapAverage() const {
    float red, green, blue;
    red   = 0;
    blue  = 0;
    green = 0;
    for (int i = 0; i < height * width; ++i) {
        red   = red + (*bitmap)[i].getPixelChannel(RED);
        green = green + (*bitmap)[i].getPixelChannel(GREEN);
        blue  = blue + (*bitmap)[i].getPixelChannel(BLUE);
    }

    red   /= height * width;
    green /= height * width;
    blue  /= height * width;
    Pixel average(red, green, blue);
    return average;
}
