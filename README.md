# Video Processing Project in c++
===========================================

This project is a video processing application that leverages **OpenCV** and **GStreamer** to perform various operations on video files. The functionalities include trimming, resizing, rotating, adding text overlays, applying filters, changing playback speed, and converting the processed video to a different format.

## Features

- **Conversion:** Convert video files from one format to another (MP4 to AVI).
- **Trimming:** Trim specific portions of the video.
- **Resizing:** Resize the video to specified dimensions.
- **Rotation:** Rotate the video by a specified angle.
- **Text Overlay:** Add dynamic or static text to the video.
- **Filter Application:** Apply filters such as grayscale.
- **Playback Speed Adjustment:** Change the playback speed of the video.
- **Face Detection:** Detect faces within the video frames and highlight them.

## Requirements

- C++11 or later
- OpenCV
- GStreamer
- CMake
- A modern C++ compiler (e.g., GCC, Clang, or MSVC)

## Installation Requirements
Before installing the project, make sure the following software is installed:

### Required Software
1. **OpenCV**:
   - Download and install OpenCV from the official website: [OpenCV Download](https://opencv.org/releases/)
   - Ensure you have version 4.5 or higher installed.

2. **GStreamer**:
   - Download and install GStreamer from the official website: [GStreamer Download](https://gstreamer.freedesktop.org/download/)
   - Choose the version suitable for Windows (msvc_x86_64).

3. **CMake**:
   - Download and install CMake from the official website: [CMake Download](https://cmake.org/download/)

## Installation build and run
To install build and run the project on your computer, follow these steps:

1. **Clone the repository**:
 ```bash
   git clone https://github.com/Hades1221/Project-Image-Processing.git
 ```

2. **Build the project**:
 ```bash
   mkdir build
 ``` 
 ```bash
   cd build
 ```
 ```bash
   cmake ..
 ```
 ```bash
   cmake --build . --config Debug
 ```
  ```bash
   cd Debug
 ```
3. **Run the application**:
 ```bash
   .\VideoProcessor.exe  <"C:\path\to\yourfile.mp4"> 
 ```

  - Press Esc to stop



### Troubleshooting
If you encounter any issues during the build process, please check the following:
- Ensure that all dependencies are installed correctly.
- Verify that the paths to OpenCV and GStreamer are set properly in CMake.
- Check the output logs for any error messages.
