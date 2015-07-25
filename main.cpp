

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

#include <ImfRgbaFile.h>

#include "Image.h"


const std::string InputColorPattern = "out.RGB_color.%04d.exr";
const std::string InputDepthPattern = "out.VRayZDepth.%04d.exr";
const size_t MAX_PATTERN_LEN = 255;


// Forms a name
std::string PatternToName(const std::string& pattern, int index) {
    char fileName[255];
    snprintf(fileName, 255, pattern.c_str(), 1);
    return std::string( fileName );
}

int main(int argc, char *argv[]) {

    printf("\n=============================\n");
    printf("Randy depth composer utility\n");
    printf("Usage : dcompose <number of frames>\n");
    printf("\n");

    Image depth(fileName);

    return 0;
}
