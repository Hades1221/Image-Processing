#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor {
public:
    VideoProcessor(const std::string &videoFile);
    void convertVideoFormat();
    void trimVideo(int startTime, int endTime, cv::VideoWriter &writer);
    void resizeVideo(cv::Mat &frame, double scale);
    void rotateVideo(cv::Mat &frame, int angle);
    void addTextOverlay(cv::Mat &frame, const std::string &text);
    void applyFilter(cv::Mat &frame, const std::string &filterType);
    void processVideo();

private:
    cv::VideoCapture cap;
    std::string videoFile;
};

#endif // VIDEO_PROCESSOR_H
