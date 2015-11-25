#include "maths/polyhedron.h"
#include "txtLogger.h"
#include "maths/utility.h"
namespace { 
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace maths {

Polyhedron::Polyhedron(std::vector<Vector3> points, Vector3 center)
:center(center)
{
    logger->log("Creating polyhedron...", LL_DEBUG);

    this->points = points;

    logger->log("Polyhedron has been created.");
}

Polyhedron::Polyhedron(Vector3 point1, Vector3 point2, Vector3 point3)
{
    logger->log("Creating polyhedron...", LL_DEBUG);

    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

	logger->log("Polyhedron has been created.");
}

Polyhedron::Polyhedron(std::vector<float> point)
{
	points = maths::getPointsFromVectorFloat(point);
}

Polyhedron::~Polyhedron()
{
	logger->log("Deleting polyhedron...", LL_DEBUG);

	logger->log("Polyhedron has been deleted.");
}

} // namespace maths
} // namespace id
