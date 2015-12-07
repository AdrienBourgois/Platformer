#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <GL/glew.h>
#include <vector>

namespace id {
namespace maths {

auto degToRad(float angle) -> float;
auto radToDeg(float angle) -> float;

static std::vector<GLfloat> rect =
{
    1.f, 1.f,
    -1.f, 1.f,
    -1.f, -1.f,

    -1.f, -1.f,
    1.f, -1.f,
    1.f, 1.f
};
class Vector3;	

auto degToRad(float angle) -> float;
auto radToDeg(float angle) -> float;

auto calcDistance(Vector3 pPoint, Vector3 pNormal, Vector3 sCenter, float sRayon) -> float;
auto calcDistance(Vector3 s1Center, float s1Rayon, Vector3 s2center, float s2Rayon) -> float;

class Shape
{
	public:
		static std::vector<GLfloat>const cube;
};


struct Color4
{
	Color4(float c1, float c2, float c3, float c4);
	float color[4];
};

} // namespace maths
} // namespace id

#endif // UTILITY_H_INCLUDED
