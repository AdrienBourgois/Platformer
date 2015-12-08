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

auto ColliderManager::addCollider(id::scene::MeshSceneNode* meshSceneNode, std::string id) -> void
{
    std::map<std::string, id::scene::mesh_group>::const_iterator it = meshSceneNode->getMesh()->getGroups().begin();
    Polyhedron polyhedron(id::maths::getPointsFromVectorFloat((it->second).data));
    Collider collider(polyhedron);

    std::tuple<Collider, std::string, int, id::scene::MeshSceneNode*> tuple = std::make_tuple(collider, id, (int)this->listCollider.size(), meshSceneNode);
    std::get<0>(tuple) = collider;

    this->listCollider.push_back(tuple);
}

auto ColliderManager::updateCollider() -> void
{
    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        std::map<std::string, id::scene::mesh_group>::const_iterator it = std::get<3>(this->listCollider[i])->getMesh()->getGroups().begin();
        std::get<0>(this->listCollider[i]).getPolyhedron().setPoints(calCoordFromMatrix(id::maths::getPointsFromVectorFloat((it->second).data), std::get<3>(this->listCollider[i])->AbsoluteTransformation()));
    }
}

auto ColliderManager::checkAllColisions() -> std::vector<std::pair<std::string, std::string>>
{
    this->updateCollider();

    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        std::get<0>(this->listCollider[i]).updateBoundingBox();
    }

    std::vector<std::pair<std::string, std::string>> listCollision;

    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        for (unsigned int j = i; j < this->listCollider.size(); ++j)
        {
            if (i != j && std::get<0>(this->listCollider[i]).collide(std::get<0>(this->listCollider[j])))
            {
                listCollision.push_back(std::make_pair(std::get<1>(this->listCollider[i]), std::get<1>(this->listCollider[j])));
            }
        }
    }

    return listCollision;
}

} // namespace maths
} // namespace id
