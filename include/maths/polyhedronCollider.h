#ifndef POLY2D_COLLIDER_H_INCLUDED
#define POLY2D_COLLIDER_H_INCLUDED

#include "maths/collider.h"
#include "maths/polyhedron.h"
namespace id{
namespace maths{

class PolyhedronCollider
:public virtual Collider
{
	public:
		PolyhedronCollider() = delete;
		virtual ~PolyhedronCollider();
		PolyhedronCollider(PolyhedronCollider const&) = delete;
		PolyhedronCollider(PolyhedronCollider&&) = delete;
		auto operator=(PolyhedronCollider const&) -> PolyhedronCollider& = default;
		auto operator=(PolyhedronCollider&&) -> PolyhedronCollider& = delete;

		PolyhedronCollider(Polyhedron* polyhedron);

	//	virtual auto collide(Collider* const) const -> bool override;
		virtual auto collide(SphereCollider* const) const -> bool override;
		virtual auto collide(PolyhedronCollider* const) const -> bool override;
		virtual auto collide(CubeCollider* const) const -> bool override;

		auto getPolyhedron() const -> Polyhedron* { return polyhedron; }
		auto setPolyhedron(Polyhedron* poly) -> void { polyhedron = poly; } 

	private:
		Polyhedron* polyhedron;
};

} // namespace maths
} // namespace id

#endif // POLY2D_COLLIDER_H_INCLUDED
