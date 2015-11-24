#ifndef POLY2D_COLLIDER_H_INCLUDED
#define POLY2D_COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id{
namespace maths{

class Poly2D;

class Poly2DCollider
:public virtual Collider
{
	public:
		Poly2DCollider() = delete;
		virtual ~Poly2DCollider();
		Poly2DCollider(Poly2DCollider const&) = delete;
		Poly2DCollider(Poly2DCollider&&) = delete;
		auto operator=(Poly2DCollider const&) -> Poly2DCollider& = delete;
		auto operator=(Poly2DCollider&&) -> Poly2DCollider& = delete;

		Poly2DCollider(Poly2D const& poly2d);

		virtual auto collide(Collider const&) const -> bool override;
		virtual auto collide(SphereCollider const&) const -> bool override;
		virtual auto collide(Poly2DCollider const&) const -> bool override;
		virtual auto collide(CubeCollider const&) const -> bool override;

		auto getPoly2D() const -> const Poly2D& { return poly2d; }

	private:
		Poly2D const& poly2d;
};

} // namespace maths
} // namespace id

#endif // POLY2D_COLLIDER_H_INCLUDED
