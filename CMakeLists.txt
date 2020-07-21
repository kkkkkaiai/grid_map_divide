project(GridMapDivide)
cmake_minimum_required(VERSION 3.10)
find_package(yaml-cpp)

include_directories(
    include
)

aux_source_directory(./src DIR_SRCS)

add_executable(GridMapDivide  ${DIR_SRCS})
target_link_libraries(GridMapDivide yaml-cpp)