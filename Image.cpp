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

Image::Image(const std::string &pattern) {


    try {

        Imf::RgbaInputFile in(fileName);

        Imath::Box2i win = in.dataWindow();

        Imath::V2i dim(win.max.x - win.min.x + 1,
                win.max.y - win.min.y + 1);

        printf("Loaded EXR \"%s\", image has %dx%d \n", fileName, dim.x,
                dim.y);

        m_Data.resize(dim.x * dim.y);

        int dx = win.min.x;
        int dy = win.min.y;

        in.setFrameBuffer(m_Data.data() - dx - dy * dim.x, 1, dim.x);
        in.readPixels(win.min.y, win.max.y);
        m_Size = dim;

    } catch (Iex::BaseExc &e) {
        printf("Error loading EXR from \"%s\" err=%s \n", fileName,
                e.what());
        throw;
    }
}


    void Image::AsciPrint() const {

const int W = 80;
vector<Imf::Rgba> row(W);

        for (int y = 0; y < m_Size.y; ++y)
            for (int x = 0; x < m_Size.x; ++x) {
                { auto px = PixelAt(x, y);
cout << px << endl;
                }
            }
    }
