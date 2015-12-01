#include <cmath>

#include "txtLogger.h"
#include "maths/collider.h"
#include "maths/polyhedron.h"
#include "maths/utility.h"
#include "maths/vector.h"


namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{

Collider::Collider(Polyhedron& polyhedron)
:polyhedron(polyhedron)
{
	logger->log("Creating Collider...", LL_DEBUG);
	logger->log("Collider has been created.");
}

Collider::~Collider()
{
	logger->log("Deleting Collider...", LL_DEBUG);

	logger->log("Collider has been deleted.");	
}

auto Collider::collide(Collider const& col) const -> bool
{
    std::vector<Vector3> points1 = this->polyhedron.getPoints();
    std::vector<Vector3> points2 =   col.polyhedron.getPoints();
    
    int count_intersection = 0;

    for (unsigned int i = 0; i < points1.size(); ++i)
    {
        for (unsigned int j = 0; j < points1.size(); ++j)
        {
            if (collideRayTriangle(points1[1], points1[2], points1[3], {0,0,0}, {1,0,0}))
                ++count_intersection;
        }

        if (count_intersection != 0 && count_intersection % 2 == 0)
            return true;
        else
            count_intersection = 0;
    }

	return false;
}

} // namespace maths
} // namespace id
