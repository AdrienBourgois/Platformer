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

auto ColliderManager::addCollider(id::scene::MeshSceneNode* meshSceneNode, int id) -> void
{
    std::map<std::string, id::scene::mesh_group>::iterator it = meshSceneNode->getMesh()->getGroups().begin();
    for (unsigned int i = 0; i < (it->second).data.size(); ++i)
    {
        std::cout << "Point numero " << i << " : " << (it->second).data[i] << std::endl;
    }
    Polyhedron polyhedron(id::maths::getPointsFromVectorFloat((it->second).data));
    std::cout << "Add" << std::endl;
    for (unsigned int i = 0; i < polyhedron.getPoints().size(); ++i)
    {
        std::cout << i << " : " << polyhedron.getPoints()[i] << std::endl;
    }
    std::cout << "---------" << std::endl;
    Collider collider(polyhedron);
    std::tuple<Collider, int, int, id::scene::MeshSceneNode*> tuple = std::make_tuple(collider, id, (int)this->listCollider.size(), meshSceneNode);
    std::get<0>(tuple) = collider;

    this->listCollider.push_back(tuple);
}

auto ColliderManager::updateCollider() -> void
{
    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        std::vector<Vector3> points = calCoordFromMatrix(std::get<0>(this->listCollider[i]).getPolyhedron().getPoints(), std::get<3>(this->listCollider[i])->AbsoluteTransformation());
        std::get<0>(this->listCollider[i]).getPolyhedron().setPoints(points);
        std::cout << "Update element " << i << std::endl;
        //std::cout << calCoordFromMatrix(std::get<0>(this->listCollider[i]).getPolyhedron().getPoints(), std::get<3>(this->listCollider[i])->AbsoluteTransformation()) << std::endl;
    }
}

auto ColliderManager::checkAllColisions() -> std::vector<std::pair<int, int>>
{
    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        std::get<0>(this->listCollider[i]).updateBoundingBox();
    }

    std::vector<std::pair<int, int>> listCollision;

    for (unsigned int i = 0; i < this->listCollider.size(); ++i)
    {
        for (unsigned int j = i; j < this->listCollider.size(); ++j)
        {
            if (i != j && std::get<0>(this->listCollider[i]).collide(std::get<0>(this->listCollider[j])))
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
