#include "maths/vector.h"
#include "maths/sphere.h"
#include "txtLogger.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace maths {

Sphere::Sphere(Vector3 center, float rayon)
:center(center), rayon(rayon)
{
	logger->log("Creating Sphere...", LL_DEBUG);
	
	logger->log("Sphere has been created.");
}

Sphere::~Sphere()
{
	logger->log("Deleting sphere...", LL_DEBUG);

	logger->log("Sphere has been deleted.");
}

} // namespace maths
} // namespace id
