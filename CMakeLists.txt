cmake_minimum_required(VERSION 2.8.4)
project(cpp_json_qi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_TEST_FILES
    test/suites/test_basic.cpp
    test/suites/test_compare.cpp
    test/suites/test_conv.cpp
    test/tester.cpp)

add_executable(run_tests ${SOURCE_TEST_FILES})
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
