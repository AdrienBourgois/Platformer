#include "maths/poly2d.h"
#include "txtLogger.h"

namespace { 
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace maths {

Poly2D::Poly2D(std::vector<Vector3> points)
{
    logger->log("Creating poly2d...", LL_DEBUG);

    this->points = points;

    logger->log("Poly2D has been created.");
}

Poly2D::Poly2D(Vector3 point1, Vector3 point2, Vector3 point3)
{
    logger->log("Creating poly2d...", LL_DEBUG);

    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

	logger->log("Poly2D has been created.");
}

Poly2D::~Poly2D()
{
	logger->log("Deleting poly2d...", LL_DEBUG);

	logger->log("Poly2D has been deleted.");
}

} // namespace maths
} // namespace id
