cmake_minimum_required(VERSION 3.10)
project(Project-imege-processing)


set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib") 

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Project-imege-processing src/main.cpp)
target_link_libraries(Project-imege-processing ${OpenCV_LIBS})