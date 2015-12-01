#include <cmath>
#include <algorithm>

#include "txtLogger.h"
#include "maths/collider.h"
#include "maths/polyhedron.h"
#include "maths/utility.h"


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

auto Collider::addBoundingBox(Polyhedron const& poly) -> void
{
    std::vector<Vector3> points = poly.getPoints();

    float Xmin = (*(std::min_element(points.begin(), points.end(), less_by_x))).val[0];
    float Xmax = (*(std::min_element(points.begin(), points.end(), less_by_x))).val[0];
    float Ymin = (*(std::min_element(points.begin(), points.end(), less_by_y))).val[1];
    float Ymax = (*(std::min_element(points.begin(), points.end(), less_by_y))).val[1];
    float Zmin = (*(std::min_element(points.begin(), points.end(), less_by_z))).val[2];
    float Zmax = (*(std::min_element(points.begin(), points.end(), less_by_z))).val[2];

    this->boundingBox = std::make_pair((Vector3){Xmin, Ymin, Zmin}, (Vector3){Xmax, Ymax, Zmax});
}

auto Collider::collide(Collider const& col) const -> bool
{
    Vector3 min1 = this->boundingBox.first;
    Vector3 max1 = this->boundingBox.second;
    Vector3 min2 = col.getBoundingBox().first;
    Vector3 max2 = col.getBoundingBox().second;

    if (max1.val[0] > min2.val[0] && min1.val[0] < max2.val[0] &&
        max1.val[1] > min2.val[1] && min1.val[1] < max2.val[1] &&
        max1.val[2] > min2.val[2] && min1.val[2] < max2.val[2])
        return true;

    return false;
}

auto Collider::advancedCollide(Collider const& col) const -> bool
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
