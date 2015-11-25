#include <SDL2/SDL.h>
#include <iostream>

#include "maths/utility.h"
#include "maths/polyhedronCollider.h"
#include "maths/polyhedron.h"
#include "sceneNode.h"
#include "maths/vector.h"
#include "txtLogger.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace scene {

auto SceneNode::createSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name) -> SceneNode*
{
	SDL_assert(scn);

	auto* node = new (std::nothrow) SceneNode(scn, parent, name);
	if (!node)
	{
		logger->log("Failed at creating Scene Node in SceneNode::createSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name)", LL_ERROR);
		SDL_assert(node);
	}

	return node;
}

SceneNode::SceneNode(SceneManager* scn, SceneNode* parent, std::string const& name)
: _scn(scn), _parent(parent), _name(name), _visible(true), polyhedronCollider(nullptr) 
{
	logger->log("Creating SceneNode...", LL_DEBUG);

	
	id::maths::Polyhedron* poly = new maths::Polyhedron(maths::Shape::cube);
	id::maths::PolyhedronCollider* polyCol = new maths::PolyhedronCollider(poly);
	this->polyhedronCollider = polyCol;

	if (_parent)
		_parent->addChild(this);
	_transformation = maths::Matrix4::identity;
	_childrens = std::vector<SceneNode*>();

	nameWhitoutExtension();

	logger->log("SceneNode has been created.");
}

SceneNode::~SceneNode()
{
	logger->log("Deleting SceneNode...", LL_DEBUG);

	while (_childrens.size() > 0)
		delete _childrens.back();
	_childrens.clear();
	if (_parent)
		_parent->delChild(this);

	logger->log("SceneNode has been deleted.");
}

auto SceneNode::nameWhitoutExtension() -> void
{
	for (unsigned int i = 0; i < _name.length(); ++i)
	{
		if (_name[i] == '.')
			_name.erase(_name.begin() + i, _name.end());
	}
}

auto SceneNode::draw(video::Driver* /*drv*/) -> void
{
	//for (std::list<SceneNode*>::iterator it=this->childrens.begin(); it != this->childrens.end(); ++it)
	//	(*it)->draw(drv);
		
}

auto SceneNode::addChild(SceneNode* child) -> void
{
	SDL_assert(child);

	_childrens.push_back(child);
	child->setParent(this);
}

auto SceneNode::delChild(SceneNode* child) -> void
{
	SDL_assert(child);

	std::vector<SceneNode*>::iterator it=_childrens.begin();
	for (; it != _childrens.end(); ++it)
	{
		if ((*it) == child)
			break;
	}
	_childrens.erase(it);
}

auto SceneNode::setPosition(maths::Vector3 vec) -> void
{
	_transformation.setPosition(vec);
	polyhedronCollider->getPolyhedron()->setCenter(vec);
}

auto SceneNode::getPosition() const -> maths::Vector3
{
	return _transformation.getPosition();
}

auto SceneNode::setRotation(maths::Vector3 rot) -> void
{
	_transformation.setRotation(rot);
}

auto SceneNode::getRotation() const -> maths::Vector3
{
	return _transformation.getRotation();
}

auto SceneNode::AbsoluteTransformation() const -> maths::Matrix4
{
	if (_parent)
		return _parent->AbsoluteTransformation() * _transformation;
	else
		return _transformation;
}

auto SceneNode::addToDeletionQueue() -> void
{
	_scn->addToDeletionQueue(this);
}

} // namespace scene
} // namespace id
