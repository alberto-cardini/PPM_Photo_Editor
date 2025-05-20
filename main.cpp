#include <Image.hpp>
#include <Edge_Detection.hpp>
#include <Gaussian_Blur.hpp>
#include <base64.hpp>
#include <iostream>

int main() {

    Image i1("image_processing/input/prova4.ppm");

    Gaussian_Blur f1(3);
    f1.apply(i1);
    i1.save("image_processing/output/sunflower_blurred.ppm");

    std::vector<uint8_t> bitmap;
    for (int i = 0; i < i1.get_height() * i1.get_width(); i++) {
       bitmap.push_back(i1.get_bitmap_R()->get_matrix()[i]);
       bitmap.push_back(i1.get_bitmap_G()->get_matrix()[i]);
       bitmap.push_back(i1.get_bitmap_B()->get_matrix()[i]);
    }

    std::string payload(base64::encode(bitmap));
    std::string escape_clear = "\033[2J\033[H";
    std::string escape_code = "\x1B_Gf=24,a=T,s=" + std::to_string(i1.get_width()) + ",v=" + std::to_string(i1.get_height()) + ";" + payload + "\x1B\\";
    std::cout << escape_clear << std::endl;
    std::cout << escape_code << std::endl;
    return 0;
}