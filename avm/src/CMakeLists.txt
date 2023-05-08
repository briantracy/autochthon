cmake_minimum_required(VERSION 3.22)
project(AutochthonVirtualMachine)


file(GLOB sources *.cpp *.h)
add_executable(avm ${sources})

target_compile_features(avm PRIVATE cxx_std_17)
set_target_properties(avm PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(avm PRIVATE
    -Wall -Wextra -Wpedantic
    -Wconversion -Wuninitialized
    -fstack-protector-strong
    -fsanitize=address
    -fdiagnostics-show-template-tree
)
target_link_options(avm PRIVATE
    -fsanitize=address
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(testTarget test/basic_test.cpp)
target_link_libraries(
  testTarget
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(testTarget)


# Thinking about project structure, I think I want all the code to go in
# a library, and then have a thin main method. This allows the test target
# and main target to both link against the main body of code.