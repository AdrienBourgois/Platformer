#ifndef PLAN_COLLIDER_H_INCLUDED
#define PLAN_COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id{
namespace maths{

class Plan;
class SphereCollider;
class CubeCollider;

class PlanCollider
:public virtual collider
{
	public:
		PlanCollider() = delete;
		virtual ~PlanCollider();
		PlanCollider(PlanCollider const&) = delete;
		PlanCollider(PlanCollider&&) = delete;
		auto operator=(PlanCollider const&) -> PlanCollider& = delete;
		auto operator=(PlanCollider&&) -> PlanCollider& = delete;

		PlanCollider(Plan const& plan);

		virtual auto collide(Collider const& col) -> bool;
		virtual auto collide(SphereCollider const& col) -> bool;
		virtual auto collide(PlanCollider const& col) -> bool;
		virtual auto collide(CubeCollider const& col) -> bool;

	private:
		Plan const& plan;
};

}
}

#endif // PLAN_COLLIDER_H_INCLUDED
