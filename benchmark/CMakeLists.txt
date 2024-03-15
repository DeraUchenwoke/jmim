# Necessary so final executable contains the Google benchmark library ______________________________
message(STATUS "Finding Google benchmark library on host machine...")
find_package(benchmark REQUIRED)

message(STATUS "Including local header files...")
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(read_csv_benchmark read_csv.cpp)

message(STATUS "Linking Google benchmark library to the target...")
target_link_libraries(read_csv_benchmark PRIVATE benchmark::benchmark benchmark::benchmark_main)

