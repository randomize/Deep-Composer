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

    /// Constructors

    // Empty image
    Image();

    // Image with data
    Image(const std::string &filename);





    /// Interface

    // Reuse image's bufer if possible
    void EmplaceData(const std::string &filename);

    void PrintInfo() const;

    inline const Imf::Rgba &PixelAt(int x, int y) const { return m_Data[y * m_Size.x + x]; }
    inline Imf::Rgba &PixelAt(int x, int y) { return const_cast<Imf::Rgba&> (static_cast<const Image&>(*this).PixelAt(x,y)); }

    inline int Width()  const { return m_Size.x; }
    inline int Height()  const { return m_Size.y; }

    void SaveToPNG(const std::string& filename);

private:
    std::vector<Imf::Rgba> m_Data;
    Imath::V2i m_Size;
};

#endif // DC_IMAGE_H
