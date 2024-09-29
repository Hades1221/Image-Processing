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
    static cv::VideoWriter VideoProcessor::convertFormat(const std::string& outputFile, const cv::Size& frameSize, double fps, const std::string& outputFormat);
    // זיהוי פנים
    static cv::Mat detectFaces(const cv::Mat& frame);

    // פונקצייה לעיבוד ותצודה על המסך
    void processAndDisplay(const std::string& inputFile, const std::string& outputFormat, int startTime, int endTime, float angle, int filterType, int windowWidth, int windowHeight, const std::string& text, int textX, int textY,  float playbackSpeed, bool faceDetectionEnabled);
    
};

#endif // VIDEO_PROCESSOR_H
