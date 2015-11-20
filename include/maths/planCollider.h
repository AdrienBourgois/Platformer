#ifndef PLAN_COLLIDER_H_INCLUDED
#define PLAN_COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id{
namespace maths{

class Plan;

class PlanCollider
:public virtual Collider
{
	public:
		PlanCollider() = delete;
		virtual ~PlanCollider();
		PlanCollider(PlanCollider const&) = delete;
		PlanCollider(PlanCollider&&) = delete;
		auto operator=(PlanCollider const&) -> PlanCollider& = delete;
		auto operator=(PlanCollider&&) -> PlanCollider& = delete;

		PlanCollider(Plan const& plan);

		virtual auto collide(Collider const&) const -> bool override;
		virtual auto collide(SphereCollider const&) const -> bool override;
		virtual auto collide(PlanCollider const&) const -> bool override;
		virtual auto collide(CubeCollider const&) const -> bool override;

	private:
		Plan const& plan;
};

}
}

#endif // PLAN_COLLIDER_H_INCLUDED
