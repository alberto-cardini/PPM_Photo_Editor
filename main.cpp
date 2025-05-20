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
    std::string escape_code = "\x1B_Gf=24,s=" + std::to_string(i1.get_width()) + ",v=" + std::to_string(i1.get_height()) + ";" + payload + "\x1B_G\\";
    std::string escape_code2 = "\x1b_Gf=100,a=T,t=t;" + payload + "\x1b\\";
    std::cout << escape_code2 << std::endl;
    return 0;
}