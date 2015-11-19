#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

namespace id {
namespace maths {

struct Vector3
{
	float val[3];
	
	auto operator+(Vector3 const vector) 	-> Vector3;
	auto operator*(float& val) const 		-> Vector3;
	auto operator*=(float& val) 			-> Vector3&;
	
	auto getNormalized() const 				-> Vector3;
};

struct Vector4
{
	float val[4];
	
	auto operator+(Vector4 const vector) 	-> Vector4;
	auto operator*(float& val) const 		-> Vector4;
	auto operator*=(float& val) 			-> Vector4&;	
};

} // namespace maths

} // namespace id


std::ostream& operator<<(std::ostream& os, const id::maths::Vector3& vec);
std::ostream& operator<<(std::ostream& os, const id::maths::Vector4& vec);
#endif
