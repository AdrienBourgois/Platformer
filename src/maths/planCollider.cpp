#include "txtLogger.h"
#include "maths/planCollider.h"
#include "maths/sphereCollider.h"
#include "maths/plan.h"
#include "maths/sphere.h"
//#include "maths/cube.h"
#include "maths/utility.h"
#include "maths/vector.h"


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

	logger->log("PlanCollider has been deleted.");	
}

auto PlanCollider::collide(Collider const& col) const -> bool
{
	return col.collide(*this);
}

auto PlanCollider::collide(SphereCollider const& col) const -> bool
{

	Vector3 p1 = plan.getPoints()[0];
	Vector3 p2 = plan.getPoints()[1];
	Vector3 p3 = plan.getPoints()[2];

    Vector4 planEquat = cartEquation(p1, p2, p3);

	float collision = calcDistance(col.getSphere().getCenter(), planEquat) - col.getSphere().getRayon(); 

    std::cout << collision << std::endl;

	if (collision <= 0)
		return true;
	else
		return false;
}

auto PlanCollider::collide(PlanCollider const& col) const -> bool
{
	(void)col;
	return true;
}

auto PlanCollider::collide(CubeCollider const& col) const -> bool
{
	(void)col;
	return true;
}

} // namespace maths
} // namespace id
