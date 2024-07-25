cmake_minimum_required(VERSION 3.15)
project(project_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_GMOCK OFF)

include(FetchContent)
FetchContent_Declare(googletest
        # Specify the commit you depend on and update it regularly.
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(SOURCE_FILE
)
add_executable(run_test ${SOURCE_FILE})

target_link_libraries(run_test
        PRIVATE core
        PRIVATE gtest_main
)
gtest_discover_tests(run_test)