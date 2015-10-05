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

#ifndef SFML_GLSL_HPP
#define SFML_GLSL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>


namespace sf
{
namespace priv
{

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
        explicit Matrix(const float* pointer);

        ////////////////////////////////////////////////////////////
        /// \brief Construct implicitly from SFML transform
        ///
        /// This constructor is only supported for 3x3 and 4x4
        /// matrices.
        ///
        /// \param transform Object containing a transform.
        ///
        ////////////////////////////////////////////////////////////
        Matrix(const Transform& transform);

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
        BaseVector4();

        ////////////////////////////////////////////////////////////
        /// \brief Construct from 4 vector components
        ///
        /// \param X,Y,Z,W Components of the 4D vector
        ///
        ////////////////////////////////////////////////////////////
        BaseVector4(T X, T Y, T Z, T W);

        ////////////////////////////////////////////////////////////
        /// \brief Conversion constructor
        ///
        /// \param other 4D vector of different type
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
        explicit BaseVector4(const BaseVector4<U>& other);

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
        Vector4();

        Vector4(T X, T Y, T Z, T W);

        template <typename U>
        explicit Vector4(const Vector4<U>& other);
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
        Vector4();

        Vector4(float X, float Y, float Z, float W);

        template <typename U>
        explicit Vector4(const Vector4<U>& other);

        ////////////////////////////////////////////////////////////
        /// \brief Construct float vector implicitly from color
        ///
        /// \param color Color instance, is normalized to [0, 1]
        ///
        ////////////////////////////////////////////////////////////
        Vector4(const Color& color);
    };

#include <SFML/Graphics/Glsl.inl>

} // namespace priv


////////////////////////////////////////////////////////////
/// \brief Namespace with GLSL types
///
////////////////////////////////////////////////////////////
namespace Glsl
{

    ////////////////////////////////////////////////////////////
    /// \brief 3x3 float matrix (mat3 in GLSL)
    ///
    /// The matrix can be constructed from an array with 3x3
    /// elements, aligned in column-major order. For example,
    /// a translation by (x, y) looks as follows:
    /// \code
    /// float array[9] =
    /// {
    ///     1, 0, 0,
    ///     0, 1, 0,
    ///     x, y, 1
    /// };
    ///
    /// sf::Glsl::Mat3 matrix(array);
    /// \endcode
    ///
    /// Mat3 can also be implicitly converted from sf::Transform:
    /// \code
    /// sf::Transform transform;
    /// sf::Glsl::Mat3 matrix = transform;
    /// \endcode
    ////////////////////////////////////////////////////////////
    typedef priv::Matrix<3, 3> Mat3;

    ////////////////////////////////////////////////////////////
    /// \brief 4x4 float matrix (mat4 in GLSL)
    ///
    /// The matrix can be constructed from an array with 4x4
    /// elements, aligned in column-major order. For example,
    /// a translation by (x, y, z) looks as follows:
    /// \code
    /// float array[16] =
    /// {
    ///     1, 0, 0, 0,
    ///     0, 1, 0, 0,
    ///     0, 0, 1, 0,
    ///     x, y, z, 1
    /// };
    ///
    /// sf::Glsl::Mat4 matrix(array);
    /// \endcode
    ///
    /// Mat4 can also be implicitly converted from sf::Transform:
    /// \code
    /// sf::Transform transform;
    /// sf::Glsl::Mat4 matrix = transform;
    /// \endcode
    ////////////////////////////////////////////////////////////
    typedef priv::Matrix<4, 4> Mat4;

    ////////////////////////////////////////////////////////////
    /// \brief 2D float vector (vec2 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector2<float> Vec2;

    ////////////////////////////////////////////////////////////
    /// \brief 2D int vector (ivec2 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector2<int> Ivec2;

    ////////////////////////////////////////////////////////////
    /// \brief 2D bool vector (bvec2 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector2<bool> Bvec2;

    ////////////////////////////////////////////////////////////
    /// \brief 3D float vector (vec3 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector3<float> Vec3;

    ////////////////////////////////////////////////////////////
    /// \brief 3D int vector (ivec3 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector3<int> Ivec3;

    ////////////////////////////////////////////////////////////
    /// \brief 3D bool vector (bvec3 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef Vector3<bool> Bvec3;

    ////////////////////////////////////////////////////////////
    /// \brief 4D float vector (vec4 in GLSL)
    ///
    /// In contrast to other 4D vectors, 4D float vectors can be
    /// initialized with sf::Color instances. Each color channel
    /// is normalized from integers in [0, 255] to floating point
    /// values in [0, 1].
    /// \code
    /// sf::Glsl::Vec4 zeroVector;
    /// sf::Glsl::Vec4 vector(1.f, 2.f, 3.f, 4.f);
    /// sf::Glsl::Vec4 color = sf::Color::Cyan;
    /// \endcode
    ////////////////////////////////////////////////////////////
    typedef priv::Vector4<float> Vec4;

    ////////////////////////////////////////////////////////////
    /// \brief 4D int vector (ivec4 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef priv::Vector4<int> Ivec4;

    ////////////////////////////////////////////////////////////
    /// \brief 4D bool vector (bvec4 in GLSL)
    ///
    ////////////////////////////////////////////////////////////
    typedef priv::Vector4<bool> Bvec4;

} // namespace Glsl
} // namespace sf

#endif // SFML_GLSL_HPP


////////////////////////////////////////////////////////////
/// \namespace sf::Glsl
/// \ingroup graphics
///
/// \details The sf::Glsl namespace contains types that match
/// their equivalents in GLSL, the OpenGL shading language.
/// These types are exclusively used by the sf::Shader class.
///
/// Types that already exist in SFML, such as \ref sf::Vector2<T>
/// and \ref sf::Vector3<T>, are reused as typedefs, so you can use
/// the types in this namespace as well as the original ones.
/// Others are newly defined, such as Glsl::Vec4 or Glsl::Mat3. Their
/// actual type is an implementation detail and should not be used.
///
/// All vector types support a default constructor that
/// initializes every component to zero, in addition to a
/// constructor with one parameter for each component.
/// The components are stored in member variables called
/// x, y, z, and w.
///
/// All matrix types support a constructor with a float*
/// parameter that points to a float array of the appropriate
/// size (that is, 9 in a 3x3 matrix, 16 in a 4x4 matrix).
/// Furthermore, they can be converted from sf::Transform
/// objects.
///
/// \see sf::Shader
///
////////////////////////////////////////////////////////////
