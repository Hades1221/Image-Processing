#include "videoProcessor.h"
#include <opencv2/opencv.hpp>
#include <iostream>


double VideoProcessor::fps = 0.0; // אתחול ה-FPS
// המרה לפורמט
cv::VideoWriter VideoProcessor::convertFormat(const std::string& outputFile, const cv::Size& frameSize, double fps, const std::string& outputFormat) {
    int fourcc;

    // קביעת פורמט הווידיאו לפי בקשת המשתמש
    if (outputFormat == ".avi") {
        fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // פורמט MJPG
    } else if (outputFormat == ".mp4") {
        fourcc = cv::VideoWriter::fourcc('H', '2', '6', '4'); // פורמט MP4
    } else {
        std::cerr << "Unsupported output format." << std::endl;
        return cv::VideoWriter(); // מחזירים אובייקט ריק אם הפורמט לא נתמך
    }

    // יצירת אובייקט VideoWriter
    cv::VideoWriter writer(outputFile, fourcc, fps, frameSize, true);

    // בדיקה האם פתיחת הקובץ הצליחה
    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open the output video file for write." << std::endl;
        return cv::VideoWriter(); // מחזירים אובייקט ריק אם הפתיחה נכשלה
    }

    return writer; // מחזירים את אובייקט ה-VideoWriter
}



// סיבוב הווידיאו (Frame)
cv::Mat VideoProcessor::rotateVideo(const cv::Mat& frame, float angle) {
    if (angle == 0) {
        return frame;
    }

    // מרכז התמונה
    cv::Point center(frame.cols / 2, frame.rows / 2);
    
    // יצירת מטריצה לסיבוב
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0); // אין צורך להמיר ל-double
    cv::Mat rotatedFrame;

    // הגדרת גודל פריים כ-Size
    cv::Size frameSize(frame.cols, frame.rows);
    cv::Rect boundingBox = cv::RotatedRect(center, frameSize, angle).boundingRect();

    // עדכון המיקום של הרוטציה
    rotationMatrix.at<double>(0, 2) += boundingBox.width / 2.0 - center.x; // לא צריך להמיר ל-double
    rotationMatrix.at<double>(1, 2) += boundingBox.height / 2.0 - center.y; // לא צריך להמיר ל-double

    // סיבוב התמונה
    cv::warpAffine(frame, rotatedFrame, rotationMatrix, boundingBox.size());
    return rotatedFrame;
}



// פילטר על הווידיאו
cv::Mat VideoProcessor::applyFilter(const cv::Mat& frame, int filterType) {
    cv::Mat filteredFrame;
    if (filterType == 1) {
        // גווני אפור
        cv::cvtColor(frame, filteredFrame, cv::COLOR_BGR2GRAY);
    } else if (filterType == 2) {
        // טשטוש
        cv::GaussianBlur(frame, filteredFrame, cv::Size(15, 15), 0); // הוספת טשטוש ללא סטיית תקן
    } else {
        filteredFrame = frame; // אם לא נבחר פילטר, מחזירים את הפריים המקורי
    }
    return filteredFrame;
}

// הוספת טקסט
cv::Mat VideoProcessor::addTextOverlay(const cv::Mat& frame, const std::string& text, int textX, int textY) {
    // אם הטקסט ריק, מחזירים את הפריים המקורי
    if (text.empty()) {
        return frame;
    }

    cv::Mat frameWithText = frame;
    
    // אם לא נבחרו ערכים, נקבע מיקום ברירת מחדל
    if (textX < 0 || textY >= frame.cols) {
        textX = frame.cols / 2; // מרכז התמונה
    }
    if (textX < 0 || textY >= frame.rows) {
        textY = frame.rows - 30; // בתחתית התמונה
    }

    // הוספת הטקסט
    cv::putText(frameWithText, text, cv::Point(textX, textY), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);
    return frameWithText;
}
// פונקצייה לזיהוי פנים
cv::Mat VideoProcessor::detectFaces(const cv::Mat& frame) {
    cv::CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml"); //  עדכון הנתיב לפי התיקייה שנמצא הקובץ

    if (faceCascade.empty()) {
        std::cerr << "Error loading face cascade" << std::endl;
        return frame; // מחזירים את הפריים המקורי אם לא מצליחים לטעון את הקסדה
    }

    std::vector<cv::Rect> faces;
    cv::Mat frameGray;

    // המרת הפריים לגווני אפור
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
    
    // זיהוי הפנים
    faceCascade.detectMultiScale(frameGray, faces);

    // ציור מלבנים סביב הפנים
    cv::Mat frameWithFaces = frame.clone();
    for (const auto& face : faces) {
        cv::rectangle(frameWithFaces, face, cv::Scalar(255, 0, 0), 2); // ציור מלבן אדום סביב הפנים
    }

    return frameWithFaces;
}