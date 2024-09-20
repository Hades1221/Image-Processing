#include "../include/video_processor.h"

void VideoProcessor::resizeVideo(cv::Mat &frame, double scale) {
    cv::resize(frame, frame, cv::Size(), scale, scale);
}

void VideoProcessor::rotateVideo(cv::Mat &frame, int angle) {
    cv::Mat rotatedFrame;
    cv::rotate(frame, rotatedFrame, angle == 90 ? cv::ROTATE_90_CLOCKWISE : cv::ROTATE_90_COUNTERCLOCKWISE);
    frame = rotatedFrame; // עדכון הפריים
}

void VideoProcessor::addTextOverlay(cv::Mat &frame, const std::string &text) {
    cv::putText(frame, text, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
}

void VideoProcessor::applyFilter(cv::Mat &frame, const std::string &filterType) {
    if (filterType == "grayscale") {
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    } else if (filterType == "blur") {
        cv::blur(frame, frame, cv::Size(5, 5));
    }
}
