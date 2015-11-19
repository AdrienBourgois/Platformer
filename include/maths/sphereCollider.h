#ifndef SPHERE_COLLIDER_H_INCLUDED
#define SPHERE_COLLIDER_H_INCLUDED

namespace id {
namespace maths {

class Sphere;
class CubeCollider;
class PlanCollider

class Spherecollider
:public virtual Collider
{
    public:
        SphereCollider() = delete;
        virtual ~SphereCollider();

        SphereCollider(SphereCollider const&) = delete;
        SphereCollider(SphereCollider &&) = delete;
        auto operator=(SphereCollider const&) -> SphereCollider = delete;
        auto operator=(SphereCollider &&) -> SphereCollider = delete;

        SphereCollider (Spere const& sphere);

        virtual auto collide(Collider const& col) -> bool;
        virtual auto collide(SphereCollider const& col) -> bool;
        virtual auto collide(CubeCollider const& col) -> bool;
        virtual auto collide(PlanCollider const& col) -> bool;

    private:
        Sphere const& sphere;
};

}
}

#endif //SPHERE_COLLIDER_H_INCLUDED
