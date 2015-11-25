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

        SphereCollider (Sphere* sphere);

  //      virtual auto collide(Collider* const) const -> bool override;
        virtual auto collide(SphereCollider* const) const -> bool override;
        virtual auto collide(CubeCollider* const) const -> bool override;
        virtual auto collide(PolyhedronCollider* const) const -> bool override;

		auto getSphere() const -> const Sphere* { return sphere; }

    private:
        Sphere* sphere;
};

} // namespace maths
} // namespace id

#endif //SPHERE_COLLIDER_H_INCLUDED
