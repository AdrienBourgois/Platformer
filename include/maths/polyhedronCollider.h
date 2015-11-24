#ifndef POLY2D_COLLIDER_H_INCLUDED
#define POLY2D_COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id{
namespace maths{

class Polyhedron;

class PolyhedronCollider
:public virtual Collider
{
	public:
		PolyhedronCollider() = delete;
		virtual ~PolyhedronCollider();
		PolyhedronCollider(PolyhedronCollider const&) = delete;
		PolyhedronCollider(PolyhedronCollider&&) = delete;
		auto operator=(PolyhedronCollider const&) -> PolyhedronCollider& = delete;
		auto operator=(PolyhedronCollider&&) -> PolyhedronCollider& = delete;

		PolyhedronCollider(Polyhedron const& polyhedron);

		virtual auto collide(Collider const&) const -> bool override;
		virtual auto collide(SphereCollider const&) const -> bool override;
		virtual auto collide(PolyhedronCollider const&) const -> bool override;
		virtual auto collide(CubeCollider const&) const -> bool override;

		auto getPolyhedron() const -> const Polyhedron& { return polyhedron; }

	private:
		Polyhedron const& polyhedron;
};

} // namespace maths
} // namespace id

#endif // POLY2D_COLLIDER_H_INCLUDED
