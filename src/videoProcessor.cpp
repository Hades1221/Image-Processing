#include "videoProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

double VideoProcessor::fps = 0.0; // אתחול ה-FPS


// סיבוב הווידיאו (Frame)
cv::Mat VideoProcessor::rotateVideo(const cv::Mat& frame, int angle) {
    // תנאי לבדיקה אם השדה ריק
    if (angle == 0) {
        return frame;
    }
    cv::Point center = cv::Point(frame.cols / 2, frame.rows / 2);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Mat rotatedFrame;
    cv::warpAffine(frame, rotatedFrame, rotationMatrix, frame.size());
    return rotatedFrame;
}

// פילטר על הווידיאו
cv::Mat VideoProcessor::applyFilter(const cv::Mat& frame, int filterType) {
    cv::Mat filteredFrame;
    if (filterType == 0) {
        // גווני אפור
        cv::cvtColor(frame, filteredFrame, cv::COLOR_BGR2GRAY);
    } else if (filterType == 1) {
        // טשטוש
        cv::GaussianBlur(frame, filteredFrame, cv::Size(15, 15), 0);
    } else {
        filteredFrame = frame; // אם לא נבחר פילטר, מחזירים את הפריים המקורי
    }
    return filteredFrame;
}

// הוספת טקסט
cv::Mat VideoProcessor::addTextOverlay(const cv::Mat& frame, const std::string& text, int x, int y) {
     // תנאי לבדיקה אם הטקסט ריק מחזירים את הפריים המקורי
    if (text.empty()) {
        return frame;
    }
    cv::Mat frameWithText = frame.clone();
    cv::putText(frameWithText, text, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2); // הוספת הטקסט
    return frameWithText;
}
