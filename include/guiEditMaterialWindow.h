#ifndef GUI_EDIT_MATERIAL_WINDOW_H_INCLUDED
#define GUI_EDIT_MATERIAL_WINDOW_H_INCLUDED

#include <string>
#include <vector>
#include "meshSceneNode.h"

#include "guiWindow.h"

namespace id {

class Device;

class EditShader;
class ChangeTextureGroupWindow;

class EditMaterialWindow : public GUI_Window
{
public:
	EditMaterialWindow();
	~EditMaterialWindow();
	
	auto Display(Device* dev) 	-> void;
	
	auto getActiveNode() 						-> scene::SceneNode*	{ return _active_node; }
	auto setActiveNode(scene::SceneNode* node) 	-> void 				{ _active_node = node; }

private:
	scene::SceneNode* 			_active_node;
	std::vector<std::string> 	_shader_list;
	EditShader* 				_edit_shader_window;
	ChangeTextureGroupWindow* 	_change_texture_group_window;
};

} // namespace id

#endif // GUI_EDIT_MATERIAL_WINDOW_H_INCLUDED
