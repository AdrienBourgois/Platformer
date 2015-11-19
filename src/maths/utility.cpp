#include <cmath>

#include "maths/utility.h"
#include "maths/vector.h"

namespace id {
namespace maths {

auto degToRad(float angle) -> float
{
	return angle * M_PI / 180.f;
}

auto radToDeg(float angle) -> float
{
	return angle * 180.f / M_PI;	
}

auto calcDistance(Vector3 pPoint, Vector3 pNormal, Vector3 sCenter, float sRayon) -> float
{
	return abs(sqrt(pNormal.dotProduct(sCenter - pPoint))) - sRayon;
}

auto calcDistance(Vector3 s1Center, float s1Rayon, Vector3 s2Center, float s2Rayon) -> float
{
	return (s1Center - s2Center).norm() - (s1Rayon + s2Rayon);
}



} // namespace maths
} // namespace id
