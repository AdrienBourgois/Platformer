#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "maths/vector.h"
#include <array>

namespace id {
namespace maths {

struct Matrix3x1
{
            float   val[3];
            auto    print() const -> void;
};

struct Matrix3x3
{
            float val[9];
    
    static       Matrix3x3 const identity;
    
            auto operator*(Matrix3x3 const& mat) const  -> Matrix3x3;
            auto operator*(Matrix3x1 const& mat) const  -> Matrix3x1;
            auto operator*=(Matrix3x3 const& mat)       -> Matrix3x3&;
            auto operator-() const                      -> Matrix3x3;
    
            auto print() const -> void;
};

struct Matrix4x4
{
    Matrix4x4() {}
    Matrix4x4(std::array<float, 16> v) : val(v) {}
    std::array<float, 16> val;
    
    static       Matrix4x4 const identity;
    static  auto perspective(float fovy, float aspect, float near, float far) -> Matrix4x4;
    
    static  auto translate(float x, float y, float z)   -> Matrix4x4;
    static  auto scale(float x, float y, float z)       -> Matrix4x4;
    static  auto scale(float s)                         -> Matrix4x4;
    static  auto rotateX(float angle) -> Matrix4x4;
    static  auto rotateY(float angle) -> Matrix4x4;
    static  auto rotateZ(float angle) -> Matrix4x4;
    
            auto operator*(Matrix4x4 const& mat) const  -> Matrix4x4;
            auto operator*=(Matrix4x4 const& mat)       -> Matrix4x4&;
    
            auto getInverse() const                     -> Matrix4x4;
    
            auto setPosition(Vector3 vec)               -> void;
            auto getPosition() const                    -> Vector3;
    
            auto setRotation(Vector3 rot)               -> void;
            auto getRotation() const                    -> Vector3;

            auto setScale(Vector3 sca)	                -> void;
            auto getScale() const 	                    -> Vector3;
    
            auto print() const                          -> void;
    
            auto Forward()                              -> Vector3;
    
            auto getMatrixRotation()                    -> Matrix3x3;
            auto getMatrixTranslation()                 -> Matrix3x1;
private:
    Vector3 _rotation;
};

typedef Matrix4x4 Matrix4;
typedef Matrix3x3 Matrix3;

} // namespace maths

} // namespace id

#endif // MATRIX_H_INCLUDED
