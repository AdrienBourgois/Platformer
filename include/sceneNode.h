#ifndef SCENE_NODE_H_INCLUDED
#define SCENE_NODE_H_INCLUDED

#include <list>
#include <string>

#include "sceneManager.h"
#include "maths/matrix.h"

namespace id {

namespace maths{
	struct Vector3;
} // namespace maths

namespace scene {

class SceneNode
{
public:
	static 	auto createSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name) -> SceneNode*;

	virtual 	 ~SceneNode();
	
	virtual auto getName()  const					-> std::string 				{ return _name; }

	virtual auto nameWhitoutExtension() 			-> void;
	virtual auto draw(video::Driver* drv) 			-> void;
	virtual auto addChild(SceneNode* child) 		-> void;
	virtual auto delChild(SceneNode* child) 		-> void;
	
	virtual auto setPosition(maths::Vector3 vec) 	-> void;
	virtual auto getPosition() const 				-> maths::Vector3;
	
	virtual auto setRotation(maths::Vector3 rot) 	-> void;
	virtual auto getRotation() const 				-> maths::Vector3;

	virtual auto setScale(maths::Vector3 sca) 		-> void;
	virtual auto getScale() const 					-> maths::Vector3;
	
	virtual auto getTransformation() const 			-> maths::Matrix4 			{ return _transformation; }
	virtual auto setTransformation(maths::Matrix4 mat) -> void 					{ _transformation = mat; }
	virtual auto AbsoluteTransformation() const 	-> maths::Matrix4;
	
	virtual auto getChildrens() const 				-> std::vector<SceneNode*> 	{ return _childrens; }
	virtual auto getVisible() const 				-> bool 					{ return _visible; } 

	virtual auto setParent(SceneNode* node) 		-> void 					{ _parent = node; }
	virtual auto getParent() const 					-> SceneNode* 				{ return _parent; }
	virtual auto getScene() const 					-> SceneManager* 			{ return _scn; }
	
	virtual auto addToDeletionQueue() 				-> void;

protected:
	SceneNode(SceneManager* scn, SceneNode* parent, std::string const& name);
	SceneManager*			_scn;
	SceneNode* 				_parent;
	std::string 			_name;
	std::vector<SceneNode*> _childrens;
	bool 					_visible;
	
	maths::Matrix4 			_transformation;
};

} // namespace scene
} // namespace id

#endif // SCENE_NODE_H_INCLUDED
