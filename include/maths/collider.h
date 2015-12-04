#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include <utility>

#include "maths/collider.h"
#include "maths/vector.h"
#include "maths/polyhedron.h"

namespace id{
namespace maths{

class Polyhedron;

class Collider
{
    public:
        Collider(Polyhedron& polyhedron);
        ~Collider();

        Collider(Collider const&) = default; 
        Collider(Collider &&) = default;
        auto operator=(Collider const&) -> Collider& = default;
        auto operator=(Collider &&) -> Collider& = default;

        auto updateBoundingBox() -> void;

        auto collide(Collider const&) const -> bool;
        auto advancedCollide(Collider const&) const -> bool;

        auto getPolyhedron() const -> Polyhedron { return polyhedron; }
        auto getBoundingBox() const -> std::pair<Vector3, Vector3> { return boundingBox; }

    private:
        Polyhedron polyhedron;
        std::pair<Vector3, Vector3> boundingBox;
};

} // namespace maths
} // namespace id

#endif // COLLIDER_H_INCLUDED
