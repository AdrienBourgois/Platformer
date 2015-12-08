#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <vector>

namespace id {
namespace maths {

struct Vector4
{
    float val[4];
    
    auto operator+(Vector4 const vector)    -> Vector4;
    auto operator*(float& val) const        -> Vector4;
    auto operator*=(float& val)             -> Vector4&;    
};

struct Vector3
{
    float val[3];

    Vector3() = default;
    Vector3(float, float, float);
    
    auto operator+(Vector3 const vector)    -> Vector3;
    auto operator*(float& val) const        -> Vector3;
    auto operator*=(float& val)             -> Vector3&;
    auto operator-(Vector3 const vector) const  -> Vector3;
    auto operator==(Vector3 const vector) const -> bool;

    auto dotProduct(Vector3 const vec) const -> float;
    auto crossProduct(Vector3 const vec) const -> Vector3;

    auto getNormalized() const              -> Vector3;
    auto norm() const -> float;
};

struct Vector4x2
{
	float val[4][2];
};

} // namespace maths

} // namespace id

std::ostream& operator<<(std::ostream& os, const id::maths::Vector3& vec);
std::ostream& operator<<(std::ostream& os, const id::maths::Vector4& vec);

#endif // VECTOR_H_INCLUDED
