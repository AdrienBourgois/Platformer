#include <cmath>
#include <GL/glew.h>
#include <vector>

#include "maths/utility.h"

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

} // namespace maths
} // namespace id
