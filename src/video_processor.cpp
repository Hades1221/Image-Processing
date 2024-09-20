#include "../include/video_processor.h"
#include <iostream>
#include <direct.h>
#include <sys/stat.h>

VideoProcessor::VideoProcessor(const std::string& videoFile) : cap(videoFile), videoFile(videoFile) {
    if (!cap.isOpened()) {
        throw std::runtime_error("Could not open video file: " + videoFile);
    }
     std::string extension = videoFile.substr(videoFile.find_last_of('.') + 1);
    std::cout << "Playing video file of type: " << extension << std::endl;
}

void createDirectory(const std::string& dir) {
    struct stat info;
    if (stat(dir.c_str(), &info) != 0) { // אם התיקייה לא קיימת
        if (_mkdir(dir.c_str()) != 0) {
            std::cerr << "Error: Could not create directory " << dir << " (Error code: " << errno << ")" << std::endl;
        } else {
            std::cout << "Directory created: " << dir << std::endl;
        }
    } else {
        std::cout << "Directory already exists: " << dir << std::endl;
    }
}

void VideoProcessor::trimVideo(int startTime, int endTime, cv::VideoWriter &writer) {
       double fps = cap.get(cv::CAP_PROP_FPS); // שמירה על fps כ-double
    int startFrame = static_cast<int>(startTime * fps);
    int endFrame = static_cast<int>(endTime * fps);

    cap.set(cv::CAP_PROP_POS_FRAMES, startFrame);
    cv::Mat frame;
    int currentFrame = startFrame;

    while (currentFrame <= endFrame) {
        cap >> frame;
        if (frame.empty()) break;

        // כאן מבצעים את כל פעולות העיבוד על הפריימים
        resizeVideo(frame, 0.7);
        rotateVideo(frame, 90);
        addTextOverlay(frame, "Hello Image Processing");
        applyFilter(frame, "grayscale");

        // כותבים את הפריים המעובד לקובץ הפלט
        writer.write(frame);
          cv::imshow("Processed Video", frame);
        if (cv::waitKey(30) >= 0) break; 
        currentFrame++;
    }
}


void VideoProcessor::convertVideoFormat() {
    int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D'); // פורמט AVI
    double fps = cap.get(cv::CAP_PROP_FPS);
    int frameRate = static_cast<int>(std::round(fps)); // עיגול של ה-FPS
    cv::Size frameSize(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
                       static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    std::string outputPath = "../../output/";
    createDirectory(outputPath);

    cv::VideoWriter writer(outputPath + "output.avi", fourcc, frameRate, frameSize, true);

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open the output video file." << std::endl;
        return;
    }

    
    // שחרור משאבים
    cap.release();
    writer.release();
    std::cout << "Video conversion completed!" << std::endl;
}




void VideoProcessor::processVideo() {
    convertVideoFormat(); // הפעלת המרת הווידאו כולל כל העיבוד
        // פתיחת קובץ ה-AVI המעובד
    std::string processedVideoFile = "../../output/output.avi"; // עדכן אם יש צורך
    cv::VideoCapture processedCap(processedVideoFile);

       if (!processedCap.isOpened()) {
        throw std::runtime_error("Could not open processed video file: " + processedVideoFile);
    }

    // קבלת פרמטרים מהווידאו המעובד
    double fps = processedCap.get(cv::CAP_PROP_FPS);
    cv::Size frameSize(static_cast<int>(processedCap.get(cv::CAP_PROP_FRAME_WIDTH)),
                       static_cast<int>(processedCap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    std::string outputPath = "../../output/processed_output.avi";
    cv::VideoWriter writer(outputPath, cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, frameSize, true);

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open the output video file." << std::endl;
        return;
    }

    // חיתוך ווידאו דינמי
    trimVideo(120, 240, writer); // כאן תוכל לשנות את זמני החיתוך

    // עיבודים על הווידאו החתוך
    cv::Mat frame;
    while (true) {
        processedCap >> frame; // קרא פריים
        if (frame.empty()) break; // אם אין פריימים, עצור

        // מבצעים את כל פעולות העיבוד על הפריימים
        resizeVideo(frame, 0.7); // שינוי גודל
        rotateVideo(frame, 90);   // סיבוב
        addTextOverlay(frame, "Hello Image Processing"); // הוספת טקסט
        applyFilter(frame, "grayscale"); // הוספת פילטר

        // כותבים את הפריים המעובד לקובץ הפלט
        writer.write(frame);
        cv::imshow("Processed Video", frame); // הצגת הפריים המעובד
        if (cv::waitKey(30) >= 0) break; // עצור אם נלחץ מקש
    }

    // שחרור משאבים
    processedCap.release();
    writer.release();
    std::cout << "Video processing completed and saved to " << outputPath << "!" << std::endl;
    
}
