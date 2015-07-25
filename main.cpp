

// #include "tinyexr/tinyexr.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

#include <ImfRgbaFile.h>

namespace Patterns {
    const char *InputColorPattern = "out.VRayZDepth.%04d.exr";
    const char *InputDepthPattern = "out.VRayZDepth.%04d.exr";
    const size_t MAX_PATTERN_LEN = 255;
}

void LeadZeros() {}

void LoadImage(const char *pattern, size_t index) {

    // Form a name
    static char fileName[Patterns::MAX_PATTERN_LEN];
    snprintf(fileName, Patterns::MAX_PATTERN_LEN, pattern, index);

    std::vector<Imf::Rgba> pixelBuffer;


    try
    {
        Imf::RgbaInputFile in(fileName);


        Imath::Box2i win = in.dataWindow();

        Imath::V2i dim(win.max.x - win.min.x + 1,
                win.max.y - win.min.y + 1);

        printf("Loaded EXR \"%s\", image has %dx%d ", fileName, dim.x, dim.y);

        pixelBuffer.resize(dim.x * dim.y);

        int dx = win.min.x;
        int dy = win.min.y;

        in.setFrameBuffer(pixelBuffer.data() - dx - dy * dim.x, 1, dim.x);
        in.readPixels(win.min.y, win.max.y);
    }
    catch(Iex::BaseExc & e)
    {
        printf("Error loading EXR from \"%s\" err=%s", fileName, e.what());
        return;
    }


}

int main(int argc, char *argv[]) { 

    printf("Randy depth composer utility");
    printf("Usage : dcompose <number of frames>");


    LoadImage( Patterns::InputDepthPattern, 1 );

    return 0;

}
