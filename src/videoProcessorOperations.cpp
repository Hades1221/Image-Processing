#include "../include/videoProcessor.h"
#include <filesystem>
#include <iostream>

// פונקצייה שמנגנת את הווידיאו על המסך
void VideoProcessor::displayVideo(const std::string &videoFile)
{
    cv::VideoCapture processedVideo(videoFile, cv::CAP_GSTREAMER); // שימוש ב-GStreamer
    if (!processedVideo.isOpened())
    {
        throw std::runtime_error("Could not open the processed video file.");
    }

    cv::Mat frame;
    while (true)
    {
        if (!processedVideo.read(frame))
            break; // קרא את הפריים הבא
        cv::imshow("Processed Video", frame); // הצג את הפריים
        if (cv::waitKey(30) >= 0)
            break; // המתן 30 מילישניות או עצור אם המשתמש לוחץ על מקש
    }

    processedVideo.release(); // שחרור המשאבים
    cv::destroyAllWindows();  // סגור את כל החלונות
}

// פונקצייה ששומרת את הווידיאו בפורמט AVI באמצעות GStreamer
void VideoProcessor::saveVideo(const cv::Mat &videoFrames, const std::string &inputFile)
{
    // קביעת התיקייה הקיימת
    std::string outputDir = "../../output"; // תיקייה קיימת
     std::filesystem::create_directory(outputDir); // יצירת התיקייה אם אינה קיימת
    std::string outputFile = outputDir + "/video.avi"; // שינוי לפורמט AVI

    // פתיחת הווידאו המקורי כדי לקבל את ה-FPS
    cv::VideoCapture capture(inputFile, cv::CAP_GSTREAMER); // שימוש ב-GStreamer
    if (!capture.isOpened())
    {
        throw std::runtime_error("Could not open the input video file.");
    }

    // קבלת ה-FPS
    double fps = capture.get(cv::CAP_PROP_FPS);
    capture.release(); // שחרור משאבים

    // קבלת ממדי הווידיאו המעובד
    int width = videoFrames.cols;  // רוחב מהפריים הראשון
    int height = videoFrames.rows; // גובה מהפריים הראשון

    // יצירת ה-VideoWriter
    std::string gstFormat = "avimux ! filesink location=" + outputFile; // הגדרת פורמט GStreamer
    cv::VideoWriter writer(gstFormat, cv::CAP_GSTREAMER, fps, cv::Size(width, height));

    if (!writer.isOpened())
    {
        throw std::runtime_error("Could not open the output video file.");
    }

    // כתיבת הפריימים
    for (int i = 0; i < videoFrames.rows; ++i)
    {
        writer.write(videoFrames.row(i));
    }

    writer.release();
    displayVideo(outputFile);
}


// פונקצייה שמקבלת את הווידיאו ומחילה עליו את כול פונקציות העיבוד ולבסוף קוראת לפונקציית השמירה
void processVideo(const std::string &inputFile){

    VideoProcessor processor(inputFile);

    // חיתוך הווידיאו
    cv::Mat trimmedVideo = processor.trimmedVideo(120, 200);

    // שינוי גודל
    cv::Mat resizedVideo = processor.resizeVideo(trimmedVideo, 640, 480);

    // סיבוב הווידיאו ב-90 מעלות
    cv::Mat rotatedVideo = processor.rotateVideo(resizedVideo, 90);

    // הוספת טקסט
    cv::Mat videoWithText = processor.addTextOverlay(rotatedVideo, "The image processing was successful!!!");

    // החלת פילטר
    cv::Mat filteredVideo = processor.applyFilter(videoWithText);

    // שמירת הווידיאו הסופי בפורמט שונה
    processor.saveVideo(filteredVideo, inputFile);
}
