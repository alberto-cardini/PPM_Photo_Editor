cmake_minimum_required(VERSION 3.15)
project(PPM_Photo_Editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master
) # or whatever tag you want

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
FetchContent_MakeAvailable(matplotplusplus)

include_directories(inc)
include_directories(src)
add_subdirectory(test)

set(SOURCE_FILE
        src/EdgeDetection.cpp
        src/GaussianBlur.cpp
        src/Image.cpp
)

set(INCLUDE_FILE
        inc/Matrix.hpp
        inc/Filter.hpp
        inc/Edge_Detection.hpp
        inc/Gaussian_Blur.hpp
        inc/Image.hpp
)

add_executable(${PROJECT_NAME} main.cpp
        ${SOURCE_FILE}
        ${INCLUDE_FILE}
)
target_link_libraries(${PROJECT_NAME} PRIVATE matplot)
install(TARGETS ${PROJECT_NAME})