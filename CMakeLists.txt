cmake_minimum_required(VERSION 2.8.4)
project(cpp_json_qi)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include)

set(SOURCE_TEST_FILES
    include/cpp-json-qi/detail/json_format.h
    include/cpp-json-qi/detail/json_symbols.h
    include/cpp-json-qi/json.h
    include/cpp-json-qi/json_error.h
    include/cpp-json-qi/json_reader.h
    include/cpp-json-qi/json_types.h
    include/cpp-json-qi/json_writer.h
    test/suites/test_access.cpp
    test/suites/test_basic.cpp
    test/suites/test_compare.cpp
    test/suites/test_conv.cpp
    test/suites/test_nonprintable.cpp
    test/suites/test_read.cpp
    test/suites/test_write.cpp
    test/tester.cpp)

add_executable(run_tests ${SOURCE_TEST_FILES})
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

add_executable(pretty_json examples/pretty_json.cpp)

add_test(TestAll bin/run_tests)


add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)
