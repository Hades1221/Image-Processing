#include <iostream>
#include <filesystem>
#include "../include/videoProcessor.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_video>" << std::endl;
        return -1;
    }

    try {
        // זימון הפונקצייה של פונקציות העיבוד
        processVideo(argv[1]);  // כאן הפונקציה משתמשת ב-GStreamer
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
