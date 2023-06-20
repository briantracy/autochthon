cmake_minimum_required(VERSION 3.22)
project(AutochthonVirtualMachine)

# Suggested cmake invocation:
# cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S src -B build

# There are four targets:
#  1. The avm library (most code here)
#  2. The avm driver binary (just a main method, links to libavm)
#  3. The test binary (google test, links to libavm)
#  4. The fuzz binary (links to libfuzz, libavm)

if (NOT NO_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

### libavm
file(GLOB libSources lib/include/libavm/*.h lib/*.cpp)
add_library(avm ${libSources})
target_compile_features(avm PUBLIC cxx_std_17)

# target_compile_definitions(avm PRIVATE _FORTIFY_SOURCE=3) # apple clang is bad
set_target_properties(avm PROPERTIES CXX_EXTENSIONS OFF)
target_compile_options(avm PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion
    -Wshadow -Wfloat-equal -Wundef -Wcast-align
    -fstack-protector-strong -ftrapv
    -Wnrvo
    -fdiagnostics-show-template-tree
)
target_include_directories(avm PRIVATE lib/include)


### avmdriver
add_executable(avmdriver driver/main.cpp)
target_include_directories(avmdriver PRIVATE lib/include)
target_link_libraries(avmdriver avm)


### avmtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB testSources test/*.cpp)
add_executable(avmtest ${testSources})
target_compile_options(avmtest PRIVATE -fvisibility=hidden)
target_include_directories(avmtest PRIVATE lib/include)
target_link_libraries(avmtest GTest::gtest_main avm)
include(GoogleTest)
gtest_discover_tests(avmtest)


### avmfuzz
# add_executable(avmfuzz fuzz/fuzzer.cpp)
# target_link_libraries(avmfuzz avm)
# target_include_directories(avmfuzz PRIVATE lib/include)
# target_compile_options(avmfuzz PRIVATE -fsanitize=fuzzer)