#include "videoProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

// פונקציה עיקרית לעיבוד הווידיאו
void VideoProcessor::processAndDisplay(const std::string& inputFile, const std::string& outputFormat, int startTime, int endTime, float angle, int filterType, int windowWidth, int windowHeight, const std::string& text, int textX, int textY, float playbackSpeed, bool faceDetectionEnabled) {
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
    
    // חישוב זמן ההמתנה בין פריימים
    int waitTime = static_cast<int>(1000 / (fps * playbackSpeed)); // זמן המתנה ב-milliseconds

    // קביעת מספר הפריימים לדלג עליהם
    int skipFrames = 3; // ניתן לשנות את המספר הזה לפי הצורך

    // החלת הפונקציות על הפריימים
    int frameCount = 0; // משתנה לספירת פריימים


    // החלת הפונקציות על הפריימים
    while (true) {
        cv::Mat frame;
        cap >> frame; // קריאה של הפריימים
        if (frame.empty() || cap.get(cv::CAP_PROP_POS_FRAMES) > endFrame) break; // יציאה אם המסגרת ריקה או אם עברנו את סוף הסרטון

       // בדיקה אם לדלג על הפריים הנוכחי
        if (frameCount % (skipFrames + 1) != 0) {
            frameCount++; // מעדכן את מספר הפריימים
            continue; // לדלג על עיבוד הפריים הזה
        }

        
        // סיבוב, החלת פילטר והוספת טקסט
        frame = rotateVideo(frame, angle);
        frame = applyFilter(frame, filterType);
        frame = addTextOverlay(frame, text, textX, textY);

        // אם המשתמש רוצה זיהוי פנים
        if (faceDetectionEnabled) {
            frame = detectFaces(frame); // קריאה לפונקציית זיהוי הפנים
        }

        // הצגת הפריימים בעיבוד
        cv::imshow("Processing Video", frame);
        
        // המתנה על פי מהירות הנגינה
        if (cv::waitKey(waitTime) >= 0) break; // עצירה אם נלחץ על מקש
    }

    cap.release(); // שחרור המשאב
    cv::destroyAllWindows(); // סגירת חלונות
}
