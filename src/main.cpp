#include <iostream>
#include "videoProcessor.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input video>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    // קבלת זמני חיתוך
    int startTime = 0, endTime = -1; // ברירת מחדל: ההתחלה היא 0, והסוף יוגדר בהמשך
    std::string startTimeInput, endTimeInput;

    std::cout << "Enter start time (seconds) (press Enter to skip, default is 0): ";
    std::getline(std::cin, startTimeInput);
    if (!startTimeInput.empty()) {
        startTime = std::stoi(startTimeInput); // אם המשתמש הכניס ערך, הופכים אותו למספר שלם
    }

    std::cout << "Enter end time (seconds) (press Enter to skip, default is until the end): ";
    std::getline(std::cin, endTimeInput);
    if (!endTimeInput.empty()) {
        endTime = std::stoi(endTimeInput); // אם המשתמש הכניס ערך, הופכים אותו למספר שלם
    }
    // קבלת זווית סיבוב
    int angle;
    std::cout << "Enter rotation angle (press Enter to skip): ";
    std::cin >> angle;

    // קבלת סוג פילטר
    int filterType;
    std::cout << "Enter filter type [option: 0 for Grayscale, 1 for Blur] (press Enter to skip): ";
    std::cin >> filterType;

    // קבלת גודל חלון
    int windowWidth, windowHeight;
    std::cout << "Enter window width (press Enter to skip): ";
    std::cin >> windowWidth;
    std::cout << "Enter window height (press Enter to skip): ";
    std::cin >> windowHeight;

    // קבלת טקסט
    std::string text;
    std::cout << "Enter text to overlay on video (press Enter to skip): ";
    std::cin.ignore(); // להתעלם משורת הקלט הקודמת
    std::getline(std::cin, text); // קבלת טקסט מהמשתמש
    

    int windowX = 0, windowY = 0; // ערכים דיפולטיביים לצירי X ו-Y

    if (!text.empty()) {
        // רק אם הוזן טקסט, נשאל על צירי X ו-Y
        std::cout << "Enter window X position (press Enter to skip): ";
        std::cin >> windowX;
        std::cout << "Enter window Y position (press Enter to skip): ";
        std::cin >> windowY;
    }


    // קבלת שם קובץ פלט
    std::string outputFileName;
    std::cout << "Enter output file name (without extension): ";
    std::cin >> outputFileName;

    // קבלת פורמט פלט
    std::string outputFormat;
    std::cout << "Enter output file format (e.g., .avi, .mp4): ";
    std::cin >> outputFormat;

    // קריאה לפונקציית עיבוד
    VideoProcessor::processVideo(inputFile, startTime, endTime, angle, filterType, windowWidth, windowHeight, windowX, windowY, text, outputFileName, outputFormat);

    return 0;
}
