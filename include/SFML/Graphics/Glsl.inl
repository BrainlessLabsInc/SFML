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
/// \brief Helper function to copy sf::Transform to sf::Glsl::Mat3
///
////////////////////////////////////////////////////////////
void initializeMatrix(Matrix<3, 3>& matrix, const Transform& transform);


////////////////////////////////////////////////////////////
/// \brief Helper function to copy sf::Transform to sf::Glsl::Mat4
///
////////////////////////////////////////////////////////////
void initializeMatrix(Matrix<4, 4>& matrix, const Transform& transform);


////////////////////////////////////////////////////////////
/// \brief Copy array-based matrix with given number of elements
///
/// Indirection to std::copy() to avoid inclusion of
/// <algorithm> and MSVC's annoying 4996 warning in header
///
////////////////////////////////////////////////////////////
void copyMatrix(const float* source, std::size_t elements, float* dest);


////////////////////////////////////////////////////////////
template <std::size_t Columns, std::size_t Rows>
Matrix<Columns, Rows>::Matrix(const float* pointer)
{
    copyMatrix(pointer, Columns * Rows, array);
}


////////////////////////////////////////////////////////////
template <std::size_t Columns, std::size_t Rows>
Matrix<Columns, Rows>::Matrix(const Transform& transform)
{
    initializeMatrix(*this, transform);
}


////////////////////////////////////////////////////////////
template <typename T>
BaseVector4<T>::BaseVector4() :
x(0),
y(0),
z(0),
w(0)
{
}


////////////////////////////////////////////////////////////
template <typename T>
BaseVector4<T>::BaseVector4(T X, T Y, T Z, T W) :
x(X),
y(Y),
z(Z),
w(W)
{
}


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
BaseVector4<T>::BaseVector4(const BaseVector4<U>& other) :
x(static_cast<T>(other.x)),
y(static_cast<T>(other.y)),
z(static_cast<T>(other.z)),
w(static_cast<T>(other.w))
{
}


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector4<T>::Vector4(const Vector4<U>& other) :
BaseVector4<T>(other)
{
}


////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>::Vector4(T X, T Y, T Z, T W) :
BaseVector4<T>(X, Y, Z, W)
{
}


////////////////////////////////////////////////////////////
template <typename T>
Vector4<T>::Vector4() :
BaseVector4<T>()
{
}


////////////////////////////////////////////////////////////
inline Vector4<float>::Vector4(const Color& color) :
BaseVector4<float>(color.r / 255.f,
                   color.g / 255.f,
                   color.b / 255.f,
                   color.a / 255.f)
{
}


////////////////////////////////////////////////////////////
template <typename U>
inline Vector4<float>::Vector4(const Vector4<U>& other) :
BaseVector4<float>(other)
{
}


////////////////////////////////////////////////////////////
inline Vector4<float>::Vector4(float X, float Y, float Z, float W) :
BaseVector4<float>(X, Y, Z, W)
{
}


////////////////////////////////////////////////////////////
inline Vector4<float>::Vector4() :
BaseVector4<float>()
{
}
