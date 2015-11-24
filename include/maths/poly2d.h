#ifndef POLY2D_H_INCLUDED
#define POLY2D_H_INCLUDED

#include <vector>
#include "maths/vector.h"

namespace id {
namespace maths {

class Poly2D
{
	public:
        Poly2D(std::vector<Vector3> points);
		Poly2D(Vector3 point1 = {1,0,0}, Vector3 point2 = {0,1,0}, Vector3 point3 = {0,0,1});
		~Poly2D();
		Poly2D(Poly2D const&) = default;
		Poly2D(Poly2D&&) = default;
		auto operator=(Poly2D const&) -> Poly2D& = default;
		auto operator=(Poly2D&&) -> Poly2D& = default;


		auto getPoints() const -> const std::vector<Vector3> { return points; }

	private:
        std::vector<Vector3> points;
};

} // namespace maths
} // namespace id

#endif // POLY2D_H_INCLUDED
