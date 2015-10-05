////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Glsl.hpp>
#include <algorithm>


namespace sf
{
namespace priv
{

    ////////////////////////////////////////////////////////////
    void initializeMatrix(Matrix<3, 3>& matrix, const Transform& transform)
    {
        const float* from = transform.getMatrix(); // 4x4
        float* to = matrix.array;                  // 3x3

        // Use only left-upper 3x3 block (for a 2D transform)
        to[0] = from[ 0]; to[1] = from[ 1]; to[2] = from[ 3];
        to[3] = from[ 4]; to[4] = from[ 5]; to[5] = from[ 7];
        to[6] = from[12]; to[7] = from[13]; to[8] = from[15];
    }


    ////////////////////////////////////////////////////////////
    void initializeMatrix(Matrix<4, 4>& matrix, const Transform& transform)
    {
        // Adopt 4x4 matrix as-is
        copyMatrix(transform.getMatrix(), 4 * 4, matrix.array);
    }


    ////////////////////////////////////////////////////////////
    void copyMatrix(const float* source, std::size_t elements, float* dest)
    {
        std::copy(source, source + elements, dest);
    }

} // namespace priv
} // namespace sf
