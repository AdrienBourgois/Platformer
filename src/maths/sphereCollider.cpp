#include "txtLogger.h"
#include "maths/sphereCollider.h"
#include "maths/polyhedronCollider.h"
#include "maths/polyhedron.h"
#include "maths/sphere.h"
#include "maths/utility.h"
#include "maths/vector.h"


namespace {
    id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{
   
SphereCollider::SphereCollider(Sphere const& sphere)
:sphere(sphere)
{
    logger->log("Creating SphereCollider...", LL_DEBUG);
    logger->log("SphereCollider has been created.");
}

SphereCollider::~SphereCollider()
{
    logger->log("Deleting SphereCollider...", LL_DEBUG);

    logger->log("SphereCollider has been deleted.");	
}

/*  
auto SphereCollider::collide(Collider* const col) const -> bool
{
    return col.collide(*this);
}
*/
auto SphereCollider::collide(SphereCollider* const col) const -> bool
{
    Vector3 cs = sphere.getCenter();
    float rayon = sphere.getRayon();

    float collision = calcDistance(cs, rayon, col.sphere.getCenter(), col.sphere.getRayon());

    if (collision <= 0)
        return true;
    else
        return false;
}

auto SphereCollider::collide(PolyhedronCollider* const col) const -> bool
{
    Vector3 p1 = col.getPolyhedron().getPoints()[0];
    Vector3 p2 = col.getPolyhedron().getPoints()[1];
    Vector3 p3 = col.getPolyhedron().getPoints()[2];
    Vector3 cs = sphere.getCenter();
    float rayon = sphere.getRayon();

    Vector3 pNormal = (p2 - p1).crossProduct(p3 - p1);

    float collision = calcDistance(p1, pNormal, cs, rayon);

    if (collision <= 0)
        return true;
    else
        return false;
}

auto SphereCollider::collide(CubeCollider* const col) const -> bool
{
	(void)col;
	return true;
}

} // namespace maths
} // namespace id
