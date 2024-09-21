#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <filesystem>

class VideoProcessor {
public:
    VideoProcessor(const std::string& inputFile);
    cv::Mat trimmedVideo(int startTime, int endTime);
    cv::Mat rotateVideo(const cv::Mat& videoFrames, int angle);
    cv::Mat addTextOverlay(const cv::Mat& videoFrames, const std::string& text);
    cv::Mat applyFilter(const cv::Mat& videoFrames);
    cv::Mat rotateVideo(const cv::Mat& videoFrames);
    cv::Mat resizeVideo(const cv::Mat& videoFrames, int newWidth, int newHeight);
    void displayVideo(const std::string& videoFile);
    void saveVideo(const cv::Mat& videoFrames, const std::string& inputFile);

private:
    cv::VideoCapture capture;
};

void processVideo(const std::string& inputFile);


#endif // VIDEOPROCESSOR_H
