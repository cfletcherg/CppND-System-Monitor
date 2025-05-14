cmake_minimum_required(VERSION 3.14)
project(monitor LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS} include)

file(GLOB ALL_SRC "src/*.cpp")
add_executable(monitor ${ALL_SRC})
target_compile_options(monitor PRIVATE -Wall -Wextra)
target_link_libraries(monitor PRIVATE ${CURSES_LIBRARIES})

add_executable(format_tests
  src/format.cpp
  test/format_test.cpp
)
target_compile_options(format_tests PRIVATE -Wall -Wextra)
target_link_libraries(format_tests
  PRIVATE
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(format_tests)

add_executable(linux_parser_tests
  src/linux_parser.cpp
  test/linux_parser_test.cpp
)
target_compile_options(linux_parser_tests PRIVATE -Wall -Wextra)
target_link_libraries(linux_parser_tests
  PRIVATE
    GTest::gtest_main
)
gtest_discover_tests(linux_parser_tests)

add_executable(process_tests
  src/process.cpp
  src/linux_parser.cpp
  test/process_test.cpp
)
target_compile_options(process_tests PRIVATE -Wall -Wextra)
target_link_libraries(process_tests
  PRIVATE
    GTest::gtest_main
)
gtest_discover_tests(process_tests)

add_executable(processor_tests
  src/processor.cpp
  src/linux_parser.cpp
  test/processor_test.cpp
)
target_compile_options(processor_tests PRIVATE -Wall -Wextra)
target_link_libraries(processor_tests
  PRIVATE
    GTest::gtest_main
)
gtest_discover_tests(processor_tests)