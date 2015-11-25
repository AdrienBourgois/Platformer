#include "txtLogger.h"
#include "maths/polyhedronCollider.h"
#include "maths/sphereCollider.h"
#include "maths/polyhedron.h"
#include "maths/sphere.h"
//#include "maths/cube.h"
#include "maths/utility.h"
#include "maths/vector.h"


namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{

PolyhedronCollider::PolyhedronCollider(Polyhedron const& polyhedron)
:polyhedron(polyhedron)
{
	logger->log("Creating PolyhedronCollider...", LL_DEBUG);
	logger->log("PolyhedronCollider has been created.");
}

PolyhedronCollider::~PolyhedronCollider()
{
	logger->log("Deleting PolyhedronCollider...", LL_DEBUG);

	logger->log("PolyhedronCollider has been deleted.");	
}

auto PolyhedronCollider::collide(Collider const& col) const -> bool
{
	return col.collide(*this);
}

auto PolyhedronCollider::collide(SphereCollider const& col) const -> bool
{

	Vector3 p1 = polyhedron.getPoints()[0];
	Vector3 p2 = polyhedron.getPoints()[1];
	Vector3 p3 = polyhedron.getPoints()[2];

    Vector4 polyhedronEquat = cartEquation(p1, p2, p3);

	float collision = calcDistance(col.getSphere().getCenter(), polyhedronEquat) - col.getSphere().getRayon(); 

    std::cout << collision << std::endl;

	if (collision <= 0)
		return true;
	else
		return false;
}

auto PolyhedronCollider::collide(PolyhedronCollider const& col) const -> bool
{
	Vector3 x, y, z;
	int i = 0;
	for (auto&& point : this->polyhedron.getPoints())
	{
		for (auto&& pointCol : col.getPolyhedron().getPoints())
		{
			if (i % 3 == 0)
				x = pointCol;
			else if (i % 3 == 1 )
				y = pointCol;
			else if ( i % 3 == 2 )
			{
				z = pointCol;
				Vector4 polyhedronEquat = cartEquation(x, y, z);
	
				float collision = calcDistance(point, polyhedronEquat); 
				if (collision <= 0)
					return true;
				else return false;
			}	
			++i;
		}
	}



	return false;
}

auto PolyhedronCollider::collide(CubeCollider const& col) const -> bool
{
	(void)col;
	return true;
}

} // namespace maths
} // namespace id
