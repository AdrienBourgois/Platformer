#ifndef POLYHEDRON_H_INCLUDED
#define POLYHEDRON_H_INCLUDED

#include <vector>
#include "maths/vector.h"

namespace id {
namespace maths {

class Polyhedron
{
    public:
        Polyhedron(std::vector<Vector3> points);
        Polyhedron(Vector3 point1 = {1,0,0}, Vector3 point2 = {0,1,0}, Vector3 point3 = {0,0,1});
        ~Polyhedron();

        Polyhedron(Polyhedron const&) = default;
        Polyhedron(Polyhedron&&) = default;
        auto operator=(Polyhedron const&) -> Polyhedron& = default;
        auto operator=(Polyhedron&&) -> Polyhedron& = default;

        auto getPoints() const -> const std::vector<Vector3> { return points; }
        auto setPoints(std::vector<Vector3> vec) -> void { points = vec;}
    private:
        std::vector<Vector3> points;
};

} // namespace maths
} // namespace id

#endif // POLYHEDRON_H_INCLUDED
