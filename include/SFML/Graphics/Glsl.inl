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
/// \brief Matrix type, used to set uniforms in GLSL
///
////////////////////////////////////////////////////////////
template <std::size_t Columns, std::size_t Rows>
struct Matrix
{
    ////////////////////////////////////////////////////////////
    /// \brief Construct from raw data
    ///
    /// \param pointer Points to the beginning of an array that
    ///                has the size of the matrix. The elements
    ///                are copied to the instance.
    ///
    ////////////////////////////////////////////////////////////
    explicit Matrix(const float* pointer)
    {
        copyMatrix(pointer, Columns * Rows, array);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Construct implicitly from SFML transform
    ///
    /// This constructor is only supported for 3x3 and 4x4
    /// matrices.
    ///
    /// \param transform Object containing a transform.
    ///
    ////////////////////////////////////////////////////////////
    Matrix(const Transform& transform)
    {
        initializeMatrix(*this, transform);
    }

    float array[Columns * Rows]; ///< Array holding matrix data
};

////////////////////////////////////////////////////////////
/// \brief Base class for common code in Vector4 template specializations
///
////////////////////////////////////////////////////////////
template <typename T>
struct BaseVector4
{
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor, creates a zero vector
    ///
    ////////////////////////////////////////////////////////////
    BaseVector4() :
    x(0),
    y(0),
    z(0),
    w(0)
    {
    }

    ////////////////////////////////////////////////////////////
    /// \brief Construct from 4 vector components
    ///
    /// \param X,Y,Z,W Components of the 4D vector
    ///
    ////////////////////////////////////////////////////////////
    BaseVector4(T X, T Y, T Z, T W) :
    x(X),
    y(Y),
    z(Z),
    w(W)
    {
    }

    ////////////////////////////////////////////////////////////
    /// \brief Conversion constructor
    ///
    /// \param other 4D vector of different type
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    explicit BaseVector4(const BaseVector4<U>& other) :
    x(static_cast<T>(other.x)),
    y(static_cast<T>(other.y)),
    z(static_cast<T>(other.z)),
    w(static_cast<T>(other.w))
    {
    }

    T x; ///< 1st component (X) of the 4D vector
    T y; ///< 2nd component (Y) of the 4D vector
    T z; ///< 3rd component (Z) of the 4D vector
    T w; ///< 4th component (W) of the 4D vector
};

////////////////////////////////////////////////////////////
/// \brief 4D vector type, used to set uniforms in GLSL
///
////////////////////////////////////////////////////////////
template <typename T>
struct Vector4 : BaseVector4<T>
{
    Vector4() :
    BaseVector4<T>()
    {
    }

    Vector4(T X, T Y, T Z, T W) :
    BaseVector4<T>(X, Y, Z, W)
    {
    }

    template <typename U>
    explicit Vector4(const Vector4<U>& other) :
    BaseVector4<T>(other)
    {
    }
};

////////////////////////////////////////////////////////////
/// \brief 4D vector type, used to set uniforms in GLSL
///
/// Template specialization to support sf::Color conversion
///
////////////////////////////////////////////////////////////
template <>
struct Vector4<float> : BaseVector4<float>
{
    Vector4() :
    BaseVector4<float>()
    {
    }

    Vector4(float X, float Y, float Z, float W) :
    BaseVector4<float>(X, Y, Z, W)
    {
    }

    template <typename U>
    explicit Vector4(const Vector4<U>& other) :
    BaseVector4<float>(other)
    {
    }

    ////////////////////////////////////////////////////////////
    /// \brief Construct float vector implicitly from color
    ///
    /// \param color Color instance, is normalized to [0, 1]
    ///
    ////////////////////////////////////////////////////////////
    Vector4(const Color& color) :
    BaseVector4<float>(color.r / 255.f,
                       color.g / 255.f,
                       color.b / 255.f,
                       color.a / 255.f)
    {
    }
};
