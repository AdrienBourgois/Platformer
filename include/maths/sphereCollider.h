#ifndef SPHERE_COLLIDER_H_INCLUDED
#define SPHERE_COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id {
namespace maths {

class Sphere;

class SphereCollider
:public virtual Collider
{
    public:
        SphereCollider() = delete;
        virtual ~SphereCollider();

        SphereCollider(SphereCollider const&) = delete;
        SphereCollider(SphereCollider&&) = delete;
        auto operator=(SphereCollider const&) -> SphereCollider = delete;
        auto operator=(SphereCollider&&) -> SphereCollider = delete;

        SphereCollider (Sphere const& sphere);

        virtual auto collide(Collider const& col) -> bool;
        virtual auto collide(SphereCollider const& col) -> bool;
        virtual auto collide(CubeCollider const& col) -> bool;
        virtual auto collide(PlanCollider const& col) -> bool;

		auto getSphere() const -> const Sphere& { return sphere; }

    private:
        Sphere const& sphere;
};

} // namespace maths
} // namespace id

#endif //SPHERE_COLLIDER_H_INCLUDED
