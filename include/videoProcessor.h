#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor {
public:
    static double fps; // הגדרת ה-FPS
    // פונקצייה לסיבוב
    static cv::Mat rotateVideo(const cv::Mat& frame, float angle);
    // פונקצייה להחלת פילטור
    static cv::Mat applyFilter(const cv::Mat& frame, int filterType);
    // פונקצייה להוספת טקסט
    static cv::Mat addTextOverlay(const cv::Mat& frame, const std::string& text, int textX, int textY);
    // פונקצייה לשינוי פורמט
    static cv::VideoWriter corvevFormat(const std::string& outputFormat);

    // פונקצייה לעיבוד ותצודה על המסך
    static void processAndDisplay(const std::string& inputFile, const std::string& outputFormat, int startTime, int endTime, float angle, int filterType, int windowWidth, int windowHeight, int textX, int textY, const std::string& text);
    
};

#endif // VIDEO_PROCESSOR_H
