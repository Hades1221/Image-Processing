#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_file>" << std::endl;
        return -1;
    }

    std::string videoFile = argv[1];
    
    cv::VideoCapture cap(videoFile);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file " << videoFile << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // קרא את המסגרת הבאה
        if (frame.empty()) break; // יציאה אם אין יותר מסגרות

        // כאן תוכל להוסיף פעולות על המסגרת
        cv::imshow("Video Frame", frame);

        if (cv::waitKey(30) >= 0) break; // המתן 30 מ"מ ולחץ על מקש כדי לצאת
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
