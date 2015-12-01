#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "maths/collider.h"

namespace id{
namespace maths{

class Polyhedron;

class Collider
{
	public:
		Collider() = delete;
		virtual ~Collider();
		Collider(Collider const&) = delete;
		Collider(Collider&&) = delete;
		auto operator=(Collider const&) -> Collider& = default;
		auto operator=(Collider&&) -> Collider& = delete;

		Collider(Polyhedron& polyhedron);

		auto collide(Collider const&) const -> bool;

		auto getPolyhedron() const -> Polyhedron& { return polyhedron; }
		//auto setPolyhedron(Polyhedron const& poly) -> void { polyhedron = poly;}
	private:
		Polyhedron& polyhedron;
		
};

} // namespace maths
} // namespace id

#endif // COLLIDER_H_INCLUDED
