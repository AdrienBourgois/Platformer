#include "txtLogger.h"
#include "maths/poly2dCollider.h"
#include "maths/sphereCollider.h"
#include "maths/poly2d.h"
#include "maths/sphere.h"
//#include "maths/cube.h"
#include "maths/utility.h"
#include "maths/vector.h"


namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{

Poly2DCollider::Poly2DCollider(Poly2D const& poly2d)
:poly2d(poly2d)
{
	logger->log("Creating Poly2DCollider...", LL_DEBUG);
	logger->log("Poly2DCollider has been created.");
}

Poly2DCollider::~Poly2DCollider()
{
	logger->log("Deleting Poly2DCollider...", LL_DEBUG);

	logger->log("Poly2DCollider has been deleted.");	
}

auto Poly2DCollider::collide(Collider const& col) const -> bool
{
	return col.collide(*this);
}

auto Poly2DCollider::collide(SphereCollider const& col) const -> bool
{

	Vector3 p1 = poly2d.getPoints()[0];
	Vector3 p2 = poly2d.getPoints()[1];
	Vector3 p3 = poly2d.getPoints()[2];

    Vector4 poly2dEquat = cartEquation(p1, p2, p3);

	float collision = calcDistance(col.getSphere().getCenter(), poly2dEquat) - col.getSphere().getRayon(); 

    std::cout << collision << std::endl;

	if (collision <= 0)
		return true;
	else
		return false;
}

auto Poly2DCollider::collide(Poly2DCollider const& col) const -> bool
{
	(void)col;
	return true;
}

auto Poly2DCollider::collide(CubeCollider const& col) const -> bool
{
	(void)col;
	return true;
}

} // namespace maths
} // namespace id
