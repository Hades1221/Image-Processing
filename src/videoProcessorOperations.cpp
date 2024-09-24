#include "videoProcessor.h" // תיקיית include
#include <opencv2/opencv.hpp> // opencv
#include <filesystem> // ליצירת תיקייה
#include <iostream> // פלט שגיאות

// פונקציה להמרה לפורמט שונה וליצירת תיקייה
cv::VideoWriter VideoProcessor::setupOutput(const std::string& fileName, const std::string& format) {
    // יצירת תיקיית output אם היא לא קיימת
    std::filesystem::create_directory("output");

    // בדיקה שהשם לא ריק
    if (fileName.empty()) {
        std::cerr << "Invalid output file name." << std::endl;
        return cv::VideoWriter(); // החזרת אובייקט ריק
    }

    std::string fullOutputFileName = "../../output/" + fileName + format; //  נתיב קובץ הפלט
    
    cv::VideoWriter writer(fullOutputFileName, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(640, 480)); //  לעדכן את גודל התמונה 

    return writer; 
}
// פונקצייה עיקרים לעיבוד הווידיאו
void VideoProcessor::processVideo(const std::string& inputFile, int startTime, int endTime, int angle, int filterType, int windowWidth, int windowHeight, int windowX, int windowY, const std::string& text, const std::string& outputFileName, const std::string& outputFormat) {
    cv::VideoWriter writer = setupOutput(outputFileName, outputFormat); // קריאה לפונקציית ההגדרה

    cv::VideoCapture cap(inputFile);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file." << std::endl;
        return;
    }

    fps = cap.get(cv::CAP_PROP_FPS); // קבלת ה-FPS מהווידאו
    int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT)); // קבלת מספר הפריימים הכולל
    int startFrame = static_cast<int>(std::round(startTime * fps));

    // אם endTime  לא הוזן (או שווה -1), משתמש באורך הווידיאו הכולל
    if (endTime <= 0) {
        endTime = static_cast<int>(totalFrames / fps); // קביעת זמן הסיום לאורך הסרטון
    }
    
    int endFrame = static_cast<int>(std::round(endTime * fps)); // עיגול כלפי מה הקרוב

    // ווידוא שהמספרים שהוכנסו בקלט תקינים
    if (startFrame < 0 || endFrame <= startFrame || endFrame > totalFrames) {
        std::cerr << "Invalid start or end time." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_POS_FRAMES, startFrame); // קביעת מיקום ההתחלתי 

    // קביעת גודל ומיקום החלון
    cv::namedWindow("Processing Video", cv::WINDOW_NORMAL); // אפשרות  לחלון גמיש
    cv::resizeWindow("Processing Video", windowWidth, windowHeight); // קביעת גודל החלון
    cv::moveWindow("Processing Video", windowX, windowY); // קביעת מיקום הטקסט

    while (true) {
        cv::Mat frame;
        cap >> frame; // קריאה של הפריימים
        if (frame.empty() || cap.get(cv::CAP_PROP_POS_FRAMES) > endFrame) break; // יציאה אם המסגרת ריקה או אם עברנו את סוף הסרטון

        // חיתוך, סיבוב, החלת פילטר והוספת טקסט
        frame = trimVideo(frame, startFrame, endFrame);
        frame = rotateVideo(frame, angle);
        frame = applyFilter(frame, filterType);
        frame = addTextOverlay(frame, text, 50, 50); 

        // הצגת הפריימים בעיבוד
        cv::imshow("Processing Video", frame);
        writer.write(frame); // כתיבת הפריים לקובץ
        if (cv::waitKey(30) >= 0) break; // עצירה אם נלחץ על מקש
    }

    cap.release(); // שחרור המשאב
    writer.release(); // שחרור הוידאו
    cv::destroyAllWindows(); // סגירת חלונות
}