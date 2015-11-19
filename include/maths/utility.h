#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

namespace id {
namespace maths {

class Vector3;	

auto degToRad(float angle) -> float;
auto radToDeg(float angle) -> float;

auto calcDistance(Vector3 pPoint, Vector3 pNormal, Vector3 sCenter, float sRayon) -> float;
auto calcDistance(Vector3 s1Center, float s1Rayon, Vector3 s2center, float s2Rayon) -> float;


} // namespace maths
} // namespace id

#endif // UTILITY_H_INCLUDED
