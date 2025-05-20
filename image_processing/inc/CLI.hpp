//
// Created by Alberto Cardini on 20/05/25.
//

#pragma once

#include <Image.hpp>
#include <Gaussian_Blur.hpp>
#include <Edge_Detection.hpp>
#include <base64.hpp>

#include "matplot/util/contourc.h"

namespace CLI {
    static std::string docs(
        "Usage: ppm [options] <value> \n"
        "--help or -H             = display docs\n"
        "--load or -l <path>      = loads ppm format image from specified absolute path\n"
        "--blur or -b <intensity> = applies gaussian blur\n"
        "--edge or -e             = applies Canny edge detection algorithm\n"
        "--hist or -h             = gives the image's histogram\n"
        "--show or -s             = show the image\n"
        "--save or -S <path>      = saves image to specified absolute path\n"
    );

    static std::string file_error("\x1b[1;31mError: no image loaded");
    static std::string blur_error("\x1b[1;31mError: blur value must me positive");
    static std::string not_a_command_error("\x1b[1;31mError: not a command");

    inline void parse(int argc, char *argv[]) {
        std::string command = "null";
        Image *i1 = nullptr;
        Gaussian_Blur *blur = nullptr;
        Edge_Detection *edge = nullptr;

        for (int i = 1; i < argc; ++i) {
            command = argv[i];

            if (command == "--help" || command == "-H")
                std::cout << docs << std::endl;

            else if (command == "--load" || command == "-l")
                try {
                    i1 = new Image(argv[i + 1]);
                }catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    std::cout << file_error << std::endl;
                    std::cout << docs << std::endl;
                }

            else if (command == "--blur" || command == "-b") {
                if (std::stoi(std::string(argv[i + 1])) > 0) {
                    if ( i1 != nullptr) {
                        blur = new Gaussian_Blur(std::stoi(std::string(argv[i + 1])));
                        blur->apply(*i1);
                        delete blur;
                    } else {
                        std::cout << file_error << std::endl;
                        std::cout << docs << std::endl;
                    }
                } else {
                    std::cout << blur_error << std::endl;
                }

            }else if (command == "--edge" || command == "-e") {
                if ( i1 != nullptr) {
                    edge = new Edge_Detection(50, 10);
                    edge->apply(*i1);
                    delete edge;
                } else {
                    std::cout << file_error << std::endl;
                }

            } else if (command == "--save" || command == "-S") {
                if (i1 != nullptr) {
                    i1->save(argv[i + 1]);
                    delete i1;
                }else {
                    std::cout << file_error << std::endl;
                }

            } else if (command == "--histo" || command == "-h") {
                if (i1 != nullptr) {
                    i1->show_histogram();
                    delete i1;
                }else {
                    std::cout << file_error << std::endl;
                }

            }else if (command == "--show" || command == "-s") {
                if (i1 != nullptr) {
                    std::vector<uint8_t> bitmap;
                    for (int j = 0; j < i1->get_height() * i1->get_width(); j++) {
                        bitmap.push_back(i1->get_bitmap_R()->get_matrix()[j]);
                        bitmap.push_back(i1->get_bitmap_G()->get_matrix()[j]);
                        bitmap.push_back(i1->get_bitmap_B()->get_matrix()[j]);
                    }
                    std::string payload(base64::encode(bitmap));
                    std::string escape_clear = "\033[2J\033[H";
                    std::string escape_code = "\x1B_Gf=24,a=T,s=" + std::to_string(i1->get_width()) + ",v=" + std::to_string(i1->get_height()) + ";" + payload + "\x1B\\";
                    std::cout << escape_clear << std::endl;
                    std::cout << escape_code << std::endl;
                } else {
                    std::cout << file_error << std::endl;
                }

            } else if (command == "null"){
                std::cout << not_a_command_error << std::endl;
            }
        }
    }
}


