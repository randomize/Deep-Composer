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

#include "Common.h"
#include "DepthImage.h"

#include <iostream>

DepthImage::DepthImage(const std::string &color, const std::string &depth)
    : color(color), depth(depth) {

    if (this->color.Height() != this->color.Height() ||
        this->color.Width() != this->color.Width()) {
        throw std::logic_error(
            "Image depth and color channels must have matching dimensions");
    }

    parallel_printf("Created depth image %s + %s \n", color, depth);
}

DepthImage::DepthImage() : color(), depth() {}

DepthImage &DepthImage::operator+=(const DepthImage &oth) {

    auto w = color.Width();
    auto h = color.Height();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {

            // c - color, d - depth

            // My data
            auto &c_me = color.PixelAt(x, y);
            auto &d_me = depth.PixelAt(x, y);

            // Oth data
            const auto &c_oth = oth.color.PixelAt(x, y);
            const auto &d_oth = oth.depth.PixelAt(x, y);

            // Depth test
            if (d_me.r < d_oth.r) {
                c_me = c_oth;
                d_me = d_oth;
            }
        }
    }

    return *this;
}

void DepthImage::EmplaceData(const std::string &color_filename,
                             const std::string &depth_filename) {

    color.EmplaceData(color_filename);
    depth.EmplaceData(depth_filename);
}

void DepthImage::SaveToPNG(const std::string &path) { color.SaveToPNG(path); }

void DepthImage::PrintInfo() const {
    parallel_printf("Depth image :\n");
    parallel_printf("Color channel :\n");
    color.PrintInfo();
    parallel_printf("Depth channel :\n");
    depth.PrintInfo();
}
