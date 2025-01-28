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

add_library(PPM_Editor_lib
        ${SOURCE_FILE}
        ${INCLUDE_FILE}
)

target_link_libraries(PPM_Editor_lib PRIVATE matplot)
target_include_directories(PPM_Editor_lib PUBLIC inc)
option(ENABLE_TESTS "Build test suite" ON)

if (ENABLE_TESTS)
    enable_testing()

    # include GoogleTest
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)

    # Add tests
    add_executable(project_test
            test/run_all_test.cpp
            test/Image_Test.cpp
            test/EdgeDetection_Test.cpp
            test/Matrix_Test.cpp
    )

    # Links the tests to the main lib and to GoogleTest
    target_link_libraries(project_test PRIVATE PPM_Editor_lib gtest_main)

    # Marks the test with CTest
    include(GoogleTest)
    gtest_discover_tests(project_test)

endif()

target_link_libraries(${PROJECT_NAME} PRIVATE matplot)
install(TARGETS ${PROJECT_NAME})