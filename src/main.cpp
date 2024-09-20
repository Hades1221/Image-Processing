#include "../include/video_processor.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <video_file>" << std::endl;
        return -1;
    }

    VideoProcessor vp(argv[1]);
    vp.processVideo(); 
    return 0;
}
