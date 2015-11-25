#ifndef POLY2D_H_INCLUDED
#define POLY2D_H_INCLUDED

#include <vector>
#include "maths/vector.h"

namespace id {
namespace maths {

class Polyhedron
{
	public:
        Polyhedron(std::vector<Vector3> points, Vector3 center = {0,0,0});
		Polyhedron(Vector3 point1 = {1,0,0}, Vector3 point2 = {0,1,0}, Vector3 point3 = {0,0,1});
		Polyhedron(std::vector<float> point);
		~Polyhedron();
		Polyhedron(Polyhedron const&) = default;
		Polyhedron(Polyhedron&&) = default;
		auto operator=(Polyhedron const&) -> Polyhedron& = default;
		auto operator=(Polyhedron&&) -> Polyhedron& = default;


		auto getPoints() const -> const std::vector<Vector3> { return points; }
		auto setCenter(Vector3 cent) -> void {center = cent;}
		auto getCenter() const -> Vector3 { return center; }

	private:
        std::vector<Vector3> points;
		Vector3 			 center;
};

} // namespace maths
} // namespace id

#endif // POLY2D_H_INCLUDED
