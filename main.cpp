

#include "tinyexr/tinyexr.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

namespace Patterns {
const char *InputColorPattern = "out.VRayZDepth.%04d.exr";
const char *InputDepthPattern = "out.VRayZDepth.%04d.exr";
const size_t MAX_PATTERN_LEN = 255;
}

void LeadZeros() {}

void LoadImage(const char *pattern, size_t index) {

    // Form a name
    static char filaname[Patterns::MAX_PATTERN_LEN];
    snprintf(filaname, Patterns::MAX_PATTERN_LEN, pattern, index);

    // Load image
    float *out; // width * height * RGBA
    int width;
    int height;
    const char *err;

    int ret = LoadEXR(&out, &width, &height, filaname, &err);

    if (ret != 0) {
        printf("Error loading EXR from \"%s\" code=%d\n and err=%s", filaname, ret, err);
        return;
    }

    printf("Loaded EXR \"%s\", image has %dx%d ", filaname, width, height);
    

    delete[] out;
}

int main(int argc, char *argv[]) { 

    printf("Randy depth composer utility");
    printf("Usage : dcompose <number of frames>");
    

    LoadImage( Patterns::InputDepthPattern, 1 );
    
    return 0;

}
