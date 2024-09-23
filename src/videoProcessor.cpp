#include "../include/videoProcessor.h"
#include <iostream>
// דף שמכיל את כול הפונקציות


// קונסטרוקטור: פותח את קובץ הווידיאו באמצעות GStreamer
VideoProcessor::VideoProcessor(const std::string& inputFile) : capture(inputFile, cv::CAP_GSTREAMER) {
    if (!capture.isOpened()) {
        throw std::runtime_error("Could not open input video using GStreamer."); 
    }
}


// פונקצייה לחיתוך הווידיאו
cv::Mat VideoProcessor::trimmedVideo(int startTime, int endTime) {
    capture.set(cv::CAP_PROP_POS_MSEC, startTime * 1000); // קובע מיקום התחלתי
    cv::Mat frame;
    cv::Mat trimmedVideo;

    // קרא פריימים עד הזמן הסופי
    while (capture.get(cv::CAP_PROP_POS_MSEC) < endTime * 1000 && capture.read(frame)) {
        trimmedVideo.push_back(frame.clone()); // הוסף פריימים חתוכים
    }
    return trimmedVideo;
}

// משנה את גודל הווידיאו
cv::Mat VideoProcessor::resizeVideo(const cv::Mat& videoFrames, int newWidth, int newHeight) {
    cv::Mat resizedFrames;
    for (int i = 0; i < videoFrames.rows; ++i) {
        cv::Mat frame = videoFrames.row(i);
        cv::Mat resizedFrame;
        cv::resize(frame, resizedFrame, cv::Size(newWidth, newHeight)); // שינוי גודל
        resizedFrames.push_back(resizedFrame); // מוסיף פריימים ממוזגים
    }
    return resizedFrames;
}

// פונקצייה שמסובבת את הווידיאו
cv::Mat VideoProcessor::rotateVideo(const cv::Mat& videoFrames, int angle) {
    cv::Mat rotatedFrames;
    for (int i = 0; i < videoFrames.rows; ++i) {
        cv::Mat frame = videoFrames.row(i);
        cv::Mat rotatedFrame;

        // ביצוע סיבוב לפי מה שהוגדר  
        if (angle == 90) {
            cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
        } else if (angle == 180) {
            cv::rotate(frame, rotatedFrame, cv::ROTATE_180);
        } else if (angle == 270) {
            cv::rotate(frame, rotatedFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
        } else {
            rotatedFrame = frame.clone(); // אם הסיבוב לא באופציות מחזיר לפריים המקורי
        }

        rotatedFrames.push_back(rotatedFrame);
    }
    return rotatedFrames;
}

// הוספת טקסט לתחתית המסך
cv::Mat VideoProcessor::addTextOverlay(const cv::Mat& videoFrames, const std::string& text) {
    cv::Mat framedWithText;
    for (int i = 0; i < videoFrames.rows; ++i) {
        cv::Mat frame = videoFrames.row(i);
        cv::Mat frameWithText = frame.clone();

        // הוספת הטקסט לתחתית הפריים
        cv::putText(frameWithText, text, cv::Point(10, frame.rows - 10), 
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2); // טקסט בצבע לבן

        framedWithText.push_back(frameWithText);
    }
    return framedWithText;
}


// החלת פילטר כרגע רק בגווני אפור
cv::Mat VideoProcessor::applyFilter(const cv::Mat& videoFrames) {
    cv::Mat filteredFrames;
    for (int i = 0; i < videoFrames.rows; ++i) {
        cv::Mat frame = videoFrames.row(i);
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY); // המרת צבעים לגווני אפור
        filteredFrames.push_back(grayFrame); // הוסף פריימים מעובדים
    }
    return filteredFrames;
}

