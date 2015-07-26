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

#include "Image.h"
#include "Common.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <png.h>

Image::Image() {}

Image::Image(const std::string &filename) { EmplaceData(filename); }

void Image::EmplaceData(const std::string &filename) {

    auto fn = filename.c_str();

    try {

        Imf::RgbaInputFile in(fn);

        Imath::Box2i win = in.dataWindow();

        Imath::V2i dim(win.max.x - win.min.x + 1, win.max.y - win.min.y + 1);

        parallel_printf("Loaded EXR \"%s\", image has %dx%d \n", fn, dim.x,
                        dim.y);

        size_t datalen = dim.x * dim.y;

        {
        if (m_Data.size() != datalen) {
            parallel_printf("Allocating buffer for %ld pixels\n", datalen);
            m_Data.resize(datalen);
        }
        }

        int dx = win.min.x;
        int dy = win.min.y;

        in.setFrameBuffer(m_Data.data() - dx - dy * dim.x, 1, dim.x);
        in.readPixels(win.min.y, win.max.y);
        m_Size = dim;

    } catch (Iex::BaseExc &e) {
        parallel_printf("Error loading EXR from \"%s\" err=%s \n", fn,
                        e.what());
        throw;
    }
}

void Image::PrintInfo() const {

    float avg[4] = {0, 0, 0, 0};

    auto f = PixelAt(0, 0);
    float max[4] = {f.r, f.g, f.b, f.a};
    float min[4] = {f.r, f.g, f.b, f.a};

    for (int y = 0; y < m_Size.y; y++) {
        for (int x = 0; x < m_Size.x; x++) {

            auto col = PixelAt(x, y);

            float r = col.r;
            float g = col.g;
            float b = col.b;
            float a = col.a;

            avg[0] += r;
            avg[1] += g;
            avg[2] += b;
            avg[3] += a;

            max[0] = std::max(max[0], r);
            max[1] = std::max(max[1], g);
            max[2] = std::max(max[2], b);
            max[3] = std::max(max[3], a);

            min[0] = std::min(min[0], r);
            min[1] = std::min(min[1], g);
            min[2] = std::min(min[2], b);
            min[3] = std::min(min[3], a);
        }
    }

    assert( static_cast<unsigned>(m_Size.x * m_Size.y ) == m_Data.size());

    const size_t total = m_Size.x * m_Size.y;

    parallel_printf(" Image %dx%d, \n avg {%f,%f,%f,%f} \n min {%f,%f,%f,%f} "
                    "\n  max {%f,%f,%f,%f} \n",
                    m_Size.x, m_Size.y, avg[0] / total, avg[1] / total,
                    avg[2] / total, avg[3] / total, min[0], min[1], min[2],
                    min[3], max[0], max[1], max[2], max[3], max[0]);
}

void Image::SaveToPNG(const std::string &filename) {

    FILE *fp = std::fopen(filename.c_str(), "wb");
    if (!fp)
        abort();

    png_structp png =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
        abort();

    if (setjmp(png_jmpbuf(png)))
        abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(png, info, m_Size.x, m_Size.y, 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    // png_set_filler(png, 0, PNG_FILLER_AFTER);

    std::vector<png_byte> row;
    row.resize(4 * m_Size.x * sizeof(png_byte));

    // Write image data
    for (int y = 0; y < m_Size.y; y++) {
        for (int x = 0; x < m_Size.x; x++) {

            auto col = PixelAt(x, y);

            row[x * 4] = static_cast<char>(col.r * 255);
            row[x * 4 + 1] = static_cast<char>(col.g * 255);
            row[x * 4 + 2] = static_cast<char>(col.b * 255);
            row[x * 4 + 3] = static_cast<char>(col.a * 255);
        }
        png_write_row(png, row.data());
    }

    // End write
    png_write_end(png, NULL);

    fclose(fp);
}
