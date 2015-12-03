#include "maths/colliderManager.h"
#include "txtLogger.h"

namespace {
    id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id{
namespace maths{

ColliderManager::ColliderManager()
{
    logger->log("Creating ColliderManager...", LL_DEBUG);
    logger->log("ColliderManager has been created.");
}

ColliderManager::~ColliderManager()
{
    logger->log("Deleting ColliderManager...", LL_DEBUG);
    logger->log("ColliderManager has been deleted.");
}

auto ColliderManager::addCollider(Polyhedron polyhedron, int id) -> void
{
    Collider collider(polyhedron);
    std::tuple<Collider, int, int> tuple = std::make_tuple(collider, id, (int)this->listCollider.size());

    this->listCollider.push_back(tuple);
}

auto ColliderManager::checkAllColisions() -> std::vector<std::pair<int, int>>
{
    for (int i = 0; i < this->listCollider.size(); ++i)
    {
        std::get<0>(this->listCollider[i]).updateBoundingBox();
    }

    std::vector<std::pair<int, int>> listCollision;

    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        for (unsigned int j = i; j < this->listCollider.size(); ++j)
        {
            if (std::get<0>(this->listCollider[i]).collide(std::get<0>(this->listCollider[j])))
            {
                listCollision.push_back(std::make_pair(std::get<1>(this->listCollider[i]), std::get<1>(this->listCollider[j])));
                std::cout << "Collision between element " << std::get<1>(this->listCollider[i]) << " and element " << std::get<1>(this->listCollider[j]) << std::endl;
            }
        }
    }

    return listCollision;
}

} // namespace maths
} // namespace id
