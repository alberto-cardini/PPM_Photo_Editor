cmake_minimum_required(VERSION 3.15)
project(MiniPhotoEditor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(googletest
        # Specify the commit you depend on and update it regularly.
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(inc)
include_directories(src)
include_directories(test)

set(SOURCE_FILE
        src/Image.cpp
        src/Pixel.cpp
)

set(INCLUDE_FILE
        inc/Image.hpp
        inc/Matrix.hpp
        inc/Pixel.hpp
)

add_executable(${PROJECT_NAME}
        main.cpp
        ${SOURCE_FILE}
        ${INCLUDE_FILE}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

add_test(NAME example_test COMMAND example)
