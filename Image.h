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

#ifndef DC_IMAGE_H
#define DC_IMAGE_H


#include <string>
#include <vector>

#include <ImfRgbaFile.h>


class Image {

public:

    Image(const std::string &pattern);

    void AsciPrint() const;

    // Accessors
    inline Imf::Rgba &PixelAt(int x, int y) { return m_Data[y * m_Size.x + x]; }
    inline const Imf::Rgba &PixelAt(int x, int y) const { return m_Data[y * m_Size.x + x]; }

    // Dimentions
    inline int Width()  const { return m_Size.x; }
    inline int Height()  const { return m_Size.y; }

private:

    // Data
    std::vector<Imf::Rgba> m_Data;

    // Dimensions
    Imath::V2i m_Size;
};

#endif // DC_IMAGE_H
