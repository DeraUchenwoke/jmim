cmake_minimum_required(VERSION 3.8)

project(jmim)

set(CMAKE_CXX_STANDARD 17)

# Link external static libraries _______________________________________________________________________________________
add_subdirectory(benchmark)

add_executable(main src/main.cpp)

# Include custom header files  ________________________________________________________________________
target_include_directories(main PUBLIC include)

