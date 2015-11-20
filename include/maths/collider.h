#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

namespace id{
namespace maths{

class PlanCollider;
class SphereCollider;
class CubeCollider;

class Collider
{
	public:
		virtual auto collide(Collider const&) const -> bool = 0;
		virtual auto collide(SphereCollider const&) const -> bool = 0;
		virtual auto collide(PlanCollider const&) const -> bool = 0;
		virtual auto collide(CubeCollider const&) const -> bool = 0;	
};


} // namespace maths
} // namespace id


#endif // COLLIDER_H_INCLUDED
