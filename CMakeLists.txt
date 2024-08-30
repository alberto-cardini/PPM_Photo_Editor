cmake_minimum_required(VERSION 3.15)
project(PPM_Photo_Editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include_directories(inc)
include_directories(src)
add_subdirectory(test)

set(SOURCE_FILE
        src/RGB_image.cpp
        src/EdgeDetection.cpp
        src/GaussianBlur.cpp
        src/Gray_Scale_image.cpp
)

set(INCLUDE_FILE
        inc/RGB_image.hpp
        inc/Matrix.hpp
        inc/Filter.hpp
        inc/EdgeDetection.hpp
        inc/GaussianBlur.hpp
        inc/Gray_Scale_image.hpp
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)
