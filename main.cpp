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

    auto fileName = PatternToName(InputDepthPattern, 1);
    Image depth(fileName);

    return 0;
}
