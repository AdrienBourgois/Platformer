#ifndef COLLIDERMANAGER_H_INCLUDED
#define COLLIDERMANAGER_H_INCLUDED

#include <tuple>
#include "maths/vector.h"
#include "maths/polyhedron.h"
#include "maths/collider.h"

namespace id{
namespace maths{

class ColliderManager
{
    public:
        ColliderManager();
        ~ColliderManager();

        ColliderManager(ColliderManager const&)  = default; 
        ColliderManager(ColliderManager &&) = delete;
        auto operator=(ColliderManager const&) -> ColliderManager = delete;
        auto operator=(ColliderManager &&) -> ColliderManager = delete;

        auto checkAllColisions() -> std::vector<std::pair<int, int>>;
        auto addCollider(Polyhedron, int) -> void;

    private:
        std::vector<std::tuple<Collider, int, int>> listCollider;
};

} // namespace maths
} // namespace id

#endif //COLLIDERMANAGER_H_INCLUDED
