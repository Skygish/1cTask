cmake_minimum_required(VERSION 3.19)
project(cpp_project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(cpp_project main.cpp)

enable_testing()

add_executable(test_ test.cpp)
target_link_libraries(test_ gtest_main)

add_test(test1 test_)