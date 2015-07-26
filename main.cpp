/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

#include <ImfRgbaFile.h>
// #include <omp.h>

#include "DepthImage.h"
#include "Common.h"

const std::string InputColorPattern = "out.RGB_color.%04d.exr";
const std::string InputDepthPattern = "out.VRayZDepth.%04d.exr";
const size_t MAX_PATTERN_LEN = 255;

// Forms a name
std::string PatternToName(const std::string &pattern, int index) {
    char fileName[255];
    snprintf(fileName, 255, pattern.c_str(), index);
    return std::string(fileName);
}

void PrintUsage() {
    printf("Usage : dcompose <number of frames> <pattern c1> <d1> <c2> <d2> "
           "<out>\n");
    printf("\n");
}

void Test() {

    int i = 0;
    DepthImage im_1;
    im_1.EmplaceData(PatternToName(InputColorPattern, i),
                     PatternToName(InputDepthPattern, i));

    im_1.PrintInfo();
    im_1.SaveToPNG("out.png");
}

int main(int argc, char *argv[]) {

    printf("\n=============================\n");
    printf("Randy depth composer utility");
    printf("\n=============================\n");

    /*Test();
    return 0;*/

    // omp_set_num_threads(2);

    if (argc != 7) {
        PrintUsage();
        return -1;
    }

    // Patse args
    std::string n_frames_str(argv[1]);
    std::string pat_c1(argv[2]);
    std::string pat_d1(argv[3]);
    std::string pat_c2(argv[4]);
    std::string pat_d2(argv[5]);
    std::string pat_out(argv[6]);
    int n_frames = 0;

    try {
        n_frames = std::stoi(n_frames_str);
    } catch (...) {
        printf("Can't parse %s as a number\n", n_frames_str.c_str());
        PrintUsage();
        return -1;
    }

    // Process textures, each thread gets an image and
    // reuses it over and over to avoid reallocations
    DepthImage im_1, im_2;

// #pragma omp parallel for private(im_1, im_2)
    for (int i = 0; i < n_frames; ++i) {

        // auto tid = omp_get_thread_num();
        // parallel_printf("\nThread #%d for task #%d \n\n", tid, i);

        // Image 1
        im_1.EmplaceData(PatternToName(pat_c1, i), PatternToName(pat_d1, i));

        // Image 2
        im_2.EmplaceData(PatternToName(pat_c2, i), PatternToName(pat_d2, i));

        // Compose
        im_1 += im_2;

        // Print
        //im_1.PrintInfo()

        // Save
        im_1.SaveToPNG(PatternToName(pat_out, i));
    }

    return 0;
}
