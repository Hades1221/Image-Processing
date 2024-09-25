#include "videoProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>



// פונקציה עיקרית לעיבוד הווידיאו
void VideoProcessor::processAndDisplay(const std::string& inputFile,  const std::string& outputFormat, int startTime, int endTime, float angle, int filterType, int windowWidth, int windowHeight, int windowX, int windowY, const std::string& text) {
    // קריאה לפונקציית ההמרה
    cv::VideoWriter writer = corvevFormat(outputFormat);

    cv::VideoCapture cap(inputFile);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file." << std::endl;
        return;
    }

    // קבלת ה-FPS מהווידאו
    fps = cap.get(cv::CAP_PROP_FPS); 
    int totalFrames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT)); // קבלת מספר הפריימים הכולל
    int startFrame = static_cast<int>(std::round(startTime * fps));

    // אם endTime לא הוזן (או שווה -1), משתמש באורך הווידיאו הכולל
    if (endTime <= 0) {
        endTime = static_cast<int>(totalFrames / fps); // קביעת זמן הסיום לאורך הסרטון
    }
    
    int endFrame = static_cast<int>(std::round(endTime * fps)); // עיגול כלפי מה הקרוב

    // ווידוא שהמספרים שהוכנסו בקלט תקינים
    if (startFrame < 0 || endFrame <= startFrame || endFrame > totalFrames) {
        std::cerr << "Invalid start or end time." << std::endl;
        return;
    }

    // קביעת מיקום ההתחלתי 
    cap.set(cv::CAP_PROP_POS_FRAMES, startFrame); 

    // קביעת גודל החלון
    cv::namedWindow("Processing Video", cv::WINDOW_NORMAL); // אפשרות לחלון גמיש
    cv::resizeWindow("Processing Video", windowWidth, windowHeight); // קביעת גודל החלון
    
    // החלת הפונקציות על הפריימים
    while (true) {
        cv::Mat frame;
        cap >> frame; // קריאה של הפריימים
        if (frame.empty() || cap.get(cv::CAP_PROP_POS_FRAMES) > endFrame) break; // יציאה אם המסגרת ריקה או אם עברנו את סוף הסרטון

        // סיבוב, החלת פילטר והוספת טקסט
        frame = rotateVideo(frame, angle);
        frame = applyFilter(frame, filterType);
        frame = addTextOverlay(frame, text, 50, 50); 

        // הצגת הפריימים בעיבוד
        cv::imshow("Processing Video", frame);
        writer.write(frame); // כתיבת הפריים לקובץ
        if (cv::waitKey(30) >= 0) break; // עצירה אם נלחץ על מקש
    }

    cap.release(); // שחרור המשאב
    writer.release(); // שחרור הוידיאו
    cv::destroyAllWindows(); // סגירת חלונות
}




