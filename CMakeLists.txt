cmake_minimum_required(VERSION 3.10)
project(Project-image-processing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# הגדרת מיקום OpenCV
set(OpenCV_DIR "C:/opencv/build/x64/vc16")

# חיפוש חבילת OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# חיפוש GStreamer

set (CMAKE_PREFIX_PATH "C:/gstreamer/1.0/msvc_x86_64")
find_package(GStreamer REQUIRED)
include_directories(${GSTREAMER_INCLUDE_DIRS})

# הוספת קבצים 
add_executable(Project-image-processing 
    src/main.cpp 
    src/videoProcessor.cpp 
    src/videoProcessorOperations.cpp
)

# קישור לספריות

target_link_libraries(Project-image-processing ${OpenCV_LIBS} ${GSTREAMER_LIBRARIES})
