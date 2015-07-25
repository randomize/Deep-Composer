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

#ifndef DC_DEPTHIMAGE_H
#define DC_DEPTHIMAGE_H


#include "Image.h"

class DepthImage {

public:



    /// Constructors

    // Init with color and depth filesnames
    DepthImage(const std::string &color_filename, const std::string &dept_filename);

    // Init an empty
    DepthImage();




    /// Interface

    // Replace contents with new ones
    void EmplaceData(const std::string &color_filename, const std::string &dept_filename);

    // Combine two depth images, (this = this + other)
    DepthImage &operator+=(const DepthImage &other);

    // Save color channel
    void SaveToPNG(const std::string &path);

    // Show info
    void PrintInfo() const ;
            


private:
    Image color;
    Image depth;
};


#endif
