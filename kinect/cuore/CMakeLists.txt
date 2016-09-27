cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cuore)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (cuore1 cuore1.cpp)
target_link_libraries (cuore1 ${PCL_LIBRARIES})
