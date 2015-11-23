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

} // namespace maths
} // namespace id

#endif // UTILITY_H_INCLUDED
