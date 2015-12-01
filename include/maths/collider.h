#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include <utility>

#include "maths/collider.h"
#include "maths/vector.h"

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

        auto updateBoundingBox() -> void;

		auto collide(Collider const&) const -> bool;
        auto advancedCollide(Collider const&) const -> bool;

		auto getPolyhedron() const -> Polyhedron& { return polyhedron; }
        auto getBoundingBox() const -> std::pair<Vector3, Vector3> { return boundingBox; }
		//auto setPolyhedron(Polyhedron const& poly) -> void { polyhedron = poly;}
	private:
		Polyhedron& polyhedron;
        std::pair<Vector3, Vector3> boundingBox;
		
};

} // namespace maths
} // namespace id

#endif // COLLIDER_H_INCLUDED
