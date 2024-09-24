#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor {
public:
    // פונקצייה ראשית לעיבוד הפריימים
    static void processVideo(const std::string& inputFile, int startTime, int endTime, int angle, int filterType, int windowWidth, int windowHeight, int windowX, int windowY, const std::string& text, const std::string& outputFileName, const std::string& outputFormat);
    
    // פונקצייה לחיתוך הווידיאו
    static cv::Mat trimVideo(const cv::Mat& frame, int startFrame, int endFrame);
    // פונקצייה לסיבוב הווידאו
    static cv::Mat rotateVideo(const cv::Mat& frame, int angle);
    // פונקצייה להוספת פילטרים
    static cv::Mat applyFilter(const cv::Mat& frame, int filterType);
    // פונקצייה להוספת טקסט
    static cv::Mat addTextOverlay(const cv::Mat& frame, const std::string& text, int x, int y);

private:
    // לשמור את ה-FPS 
    static double fps;
    // פונקצייה לשמירה על הווידיאו בקובץ פלט בפורמט אחר
    static cv::VideoWriter setupOutput(const std::string& fileName, const std::string& format); 
};

#endif // VIDEO_PROCESSOR_H
