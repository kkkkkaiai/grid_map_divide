project(GridMapDivide)
cmake_minimum_required(VERSION 3.10)

add_definitions(-w)

find_package(yaml-cpp)
find_package(PCL 1.7 REQUIRED)
include_directories(
    include
    ${PCL_INCLUDE_DIRS}
)
 
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(GridMapDivide  src/main_node.cpp src/readPcd.cpp)
target_link_libraries(GridMapDivide yaml-cpp ${PCL_LIBRARIES})

add_executable(Visualize  src/visualize_node.cpp src/visualize.cpp src/readPcd.cpp)
target_link_libraries(Visualize yaml-cpp ${PCL_LIBRARIES})