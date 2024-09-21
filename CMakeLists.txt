cmake_minimum_required(VERSION 3.10)
project(Project-imege-processing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenCV_DIR "C:/opencv/build")


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

# הוספת קבצים 
add_executable(Project-imege-processing 
    src/main.cpp 
    src/videoProcessor.cpp 
    src/videoProcessorOperations.cpp
)


target_link_libraries(Project-imege-processing ${OpenCV_LIBS})
