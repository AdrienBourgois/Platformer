#include "txtLogger.h"
#include "maths/planCollider.h"
#include "maths/plan.h"
#include "maths/sphere.h"
#include "maths/utility.h"


namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{

PlanCollider::PlanCollider(Plan const& plan)
:plan(plan)
{
	logger->log("Creating PlanCollider...", LL_DEBUG);
	logger->log("PlanCollider has been created.");
}

PlanCollider::~PlanCollider()
{
	logger->log("Deleting PlanCollider...", LL_DEBUG);

	plan = nullptr;

	logger->log("PlanCollider has been deleted.");	
}

auto PlanCollider::collide(Collider const& col) -> bool
{
	return col.collide(*this);
}

auto PlanCollider::collide(SphereCollider const& col) -> bool
{
	Vector3 p1 = plan->getPoints()[0];
	vector3 p2 = plan->getPoints()[1];
	vector3 p3 = plan->getPoints()[2];

	pNormal = (p2 - p1).cross(p3 - p1);

	float collision = calcDistance(p1, pNormal, col.sphere.getCenter(), col.sphere.getRayon());

	if (collision <= 0)
		return true;
	else
		return false;

}

auto PlanCollider::collide(PlanCollider const& col) -> bool
{

}

auto PlanCollider::collide(CubeCollider const& col) -> bool
{

}

} // namespace maths
} // namespace id
