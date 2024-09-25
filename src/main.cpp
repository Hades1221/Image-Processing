#include <iostream>
#include "videoProcessor.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input video>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    // הגדרות ערכים דיפולטיביים
    int startTime = 0; // ברירת מחדל: 0 שניות
    int endTime = -1;  // ברירת מחדל: עד הסוף
    float angle = 0.0;     // ברירת מחדל: ללא סיבוב
    int filterType = 0; // ברירת מחדל: ללא פילטר
    int windowWidth = 640; // ברירת מחדל: 640
    int windowHeight = 480; // ברירת מחדל: 480
    std::string text = ""; // ברירת מחדל: ללא טקסט
    std::string outputFileName = "output_video"; // ברירת מחדל: output_video
    std::string outputFormat = ".avi"; // ברירת מחדל להמרה ל-AVI
    int textX = windowWidth / 2; // מיקום X דיפולטיבי: אמצע חלון
    int textY = windowHeight - 30; // מיקום Y דיפולטיבי: בתחתית חלון

    // קבלת פורמט הפלט
    std::cout << "Select output format:" << std::endl;
    std::cout << "1 for avi" << std::endl;
    std::cout << "2 for mp4" << std::endl;
    std::string outputFormatInput;
    std::getline(std::cin, outputFormatInput);
    if (outputFormatInput == "2") {
        outputFormat = ".mp4"; // אם נבחר MP4
    }

    // קבלת זמני חיתוך
    std::string startTimeInput, endTimeInput;
    // start time
    std::cout << "Enter start time (seconds) (press Enter to skip, default is 0): ";
    std::getline(std::cin, startTimeInput);
    if (!startTimeInput.empty()) {
        startTime = std::stoi(startTimeInput);
    }
    // end time
    std::cout << "Enter end time (seconds) (press Enter to skip, default is until the end): ";
    std::getline(std::cin, endTimeInput);
    if (!endTimeInput.empty()) {
        endTime = std::stoi(endTimeInput);
    }

    // קבלת זווית סיבוב
    std::cout << "Enter rotation angle (press Enter to skip, default is 0): ";
    std::string angleInput;
    std::getline(std::cin, angleInput);
    if (!angleInput.empty()) {
        angle = static_cast<float>(std::stoi(angleInput));
    }

    // קבלת סוג פילטר
    std::cout << "Select a filter type:" <<std::endl; 
    std::cout << "1 for Grayscale" <<std::endl; 
    std::cout << "2 for Blur:" <<std::endl;
    std::string filterTypeInput;
    std::getline(std::cin, filterTypeInput);
    if (!filterTypeInput.empty()) {
        filterType = std::stoi(filterTypeInput);
    }

    // קבלת גודל חלון
    std::cout << "Enter window width (press Enter to skip, default is 640): ";
    std::string windowWidthInput;
    std::getline(std::cin, windowWidthInput);
    if (!windowWidthInput.empty()) {
        windowWidth = std::stoi(windowWidthInput);
    }

    std::cout << "Enter window height (press Enter to skip, default is 480): ";
    std::string windowHeightInput;
    std::getline(std::cin, windowHeightInput);
    if (!windowHeightInput.empty()) {
        windowHeight = std::stoi(windowHeightInput);
    }

    // קבלת טקסט
    std::cout << "Enter text to overlay (press Enter to skip, default is none): ";
    std::getline(std::cin, text);

    // אם הטקסט ריק, לא נשאל לגבי המיקום
    if (!text.empty()) {
        std::cout << "Enter text X position (press Enter to skip, default is centered): ";
        std::string textXInput;
        std::getline(std::cin, textXInput);
        if (!textXInput.empty()) {
            textX = std::stoi(textXInput);
        }

        std::cout << "Enter text Y position (press Enter to skip, default is 30 from bottom): ";
        std::string textYInput;
        std::getline(std::cin, textYInput);
        if (!textYInput.empty()) {
            textY = std::stoi(textYInput);
        }
    }

    VideoProcessor::processAndDisplay(inputFile, outputFormat, startTime, endTime, angle, filterType, windowWidth, windowHeight, textX, textY, text);
    

    return 0;
}
