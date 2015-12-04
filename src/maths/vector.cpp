#include <cmath>
#include <vector>

#include "maths/vector.h"

namespace id {
namespace maths {

Vector3::Vector3(float val0, float val1, float val2)
{
    this->val[0] = val0;
    this->val[1] = val1;
    this->val[2] = val2;
}

auto Vector3::operator+(Vector3 const vector) -> Vector3
{
    return { this->val[0] + vector.val[0], this->val[1] + vector.val[1], this->val[2] + vector.val[2] };
}

auto Vector3::operator*(float& val) const -> Vector3
{
    return { this->val[0] * val, this->val[1] * val, this->val[2] * val };
}

auto Vector3::operator*=(float& val) -> Vector3&
{
    *this = *this * val;
    return *this;
}

auto Vector3::getNormalized() const -> Vector3
{
    float ax = this->val[0];
    float ay = this->val[1];
    float az = this->val[2];
    float len = sqrt((ax*ax)+(ay*ay)+(az*az));
    return {ax/len,ay/len,az/len};
}

auto Vector3::operator-(Vector3 const vector) const -> Vector3
{
    return { this->val[0] - vector.val[0], this->val[1] - vector.val[1], this->val[2] - vector.val[2] };
}

auto Vector3::dotProduct(Vector3 const vec)const -> float
{   
    float ax = this->val[0];    float ay = this->val[1];    float az = this->val[2];
    float bx = vec.val[0];      float by = vec.val[1];      float bz = vec.val[2];

    return ax * bx + ay * by + az * bz;
}

auto Vector3::crossProduct(Vector3 const vec)const-> Vector3
{
    float ax = this->val[0];    float ay = this->val[1];    float az = this->val[2];
    float bx = vec.val[0];      float by = vec.val[1];      float bz = vec.val[2];

    return {(ay * bz - az * by), (az * bx - ax * bz), (ax * by - ay * bx)};
}

auto Vector3::norm() const -> float
{
    float x = this->val[0]; float y = this->val[1]; float z = this->val[2];
    
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

auto Vector4::operator+(Vector4 const vector) -> Vector4
{
    return { this->val[0] + vector.val[0], this->val[1] + vector.val[1], this->val[2] + vector.val[2], this->val[3] + vector.val[3] };
}

auto Vector4::operator*(float& val) const -> Vector4
{
    return { this->val[0] * val, this->val[1] * val, this->val[2] * val, this->val[3] * val };
}

auto Vector4::operator*=(float& val) -> Vector4&
{
    *this = *this * val;
    return *this;
}

} // namespace id
} // namespace maths

std::ostream& operator<<(std::ostream& os, const id::maths::Vector3& vec)
{
    os << "{ " << vec.val[0] << " , " << vec.val[1] << " , " << vec.val[2] << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const id::maths::Vector4& vec)
{
    os << "{ " << vec.val[0] << " , " << vec.val[1] << " , " << vec.val[2] << " , " << vec.val[3] << " }";
    return os;
}
