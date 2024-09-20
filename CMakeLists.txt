cmake_minimum_required(VERSION 3.10)
project(Project-imege-processing)



set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib") 

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

add_executable(Project-imege-processing 
    src/main.cpp 
    src/video_processor.cpp 
    src/video_processor_operations.cpp
)
target_link_libraries(Project-imege-processing ${OpenCV_LIBS})







