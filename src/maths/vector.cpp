#include <cmath>

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

auto Vector3::operator-(Vector3 const vector) -> Vector3
{
	return { this->val[0] - vector.val[0], this->val[1] - vector.val[1], this->val[2] - vector.val[2] };
}

auto Vector3::dotProduct(Vector3 vec) -> float
{	
	float ax = this->val[0];	float ay = this->val[1];	float az = this->val[2];
	float bx = vec.val[0];		float by = vec.val[1];		float bz = vec.val[2];

	return ax * bx + ay * by + az * bz;


}

auto Vector3::crossProduct(Vector3 vec) -> Vector3
{
	float ax = this->val[0];	float ay = this->val[1];	float az = this->val[2];
	float bx = vec.val[0];		float by = vec.val[1];		float bz = vec.val[2];
		
	return {(ay * bz - az * by), (az * bx - ax * bz), (ax * by - ay * bx)};

}

auto Vector3::norm() -> float
{
	float x = this->val[0];	float y = this->val[1];	float z = this->val[2];
	
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	
}

auto Vector3::cartEquation(Vector3 vec1, Vector3 vec2, Vector3 vec3) -> Vector4
{
    Vector3 AB = vec2 - vec1;
    Vector3 BC = vec3 - vec1;

    Vector3 M = AB.crossProduct(BC);

    int d = -((vec1.val[0] * M.val[0]) + (vec1.val[1] * M.val[1]) + (vec1.val[2] * M.val[2]));

    Vector4 equation;

    equation.val[0] = M.val[0];
    equation.val[1] = M.val[1];
    equation.val[2] = M.val[2];
    equation.val[3] = d;

    return equation;
}

auto Vector3::distancePointToPlan(Vector3 point, Vector4 plan) -> float
{
    return (abs(plan.val[0] * point.val[0] + plan.val[1] * point.val[1] + plan.val[2] * point.val[2] + plan.val[3]) / sqrt(pow(plan.val[0], 2) + pow(plan.val[1], 2) + pow(plan.val[2], 2)));
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
