//
// Created by Alberto Cardini on 20/05/24.
//
#include "Edge_Detection.hpp"
#include "Image.hpp"

int main() {
    while (1) {
        {
            try {
                std::string path;
                std::cout << "Type the path of the image in format .ppm you want to see the Histogram: \r" << std::endl;
                std::cin >> path;
                Image i1(path);
                i1.show_histogram();
            } catch (std::ifstream::failure &e) {
                std::cout << "Invalid path." << std::endl;
            }
        }
    }
}