cmake_minimum_required(VERSION 3.22)
project(AutochthonVirtualMachine)

# There are four targets:
#  1. The avm library (most code here)
#  2. The avm driver binary (just a main method, links to libavm)
#  3. The test binary (google test, links to libavm)
#  4. The fuzz binary (links to libfuzz, libavm)


file(GLOB libSources lib/include/libavm/*.h lib/*.cpp)
add_library(avm ${libSources})
target_compile_features(avm PUBLIC cxx_std_20)
set_target_properties(avm PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(avm PRIVATE
    -Wall -Wextra -Wpedantic
    -Wconversion -Wuninitialized
    -fstack-protector-strong
    -fsanitize=address
    -fdiagnostics-show-template-tree
)
target_link_options(avm PUBLIC
    -fsanitize=address
)
target_include_directories(avm PRIVATE lib/include)


add_executable(avmdriver driver/main.cpp)
target_include_directories(avmdriver PRIVATE lib/include)
target_link_libraries(avmdriver avm)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB testSources test/*.cpp)
add_executable(testTarget ${testSources})
target_include_directories(testTarget PRIVATE lib/include)
target_link_libraries(testTarget GTest::gtest_main avm)
include(GoogleTest)
gtest_discover_tests(testTarget)

