cmake_minimum_required(VERSION 3.10)
# שם הפרוייקט
project(Project-image-processing)

set(CMAKE_CXX_STANDARD 17)  # הגדרת גרסת C++ ל-17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# מציאת ספריות OPENCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} include)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# יצירת האפליקציה
add_executable(videoProcessor ${SOURCES})
target_link_libraries(videoProcessor ${OpenCV_LIBS})




