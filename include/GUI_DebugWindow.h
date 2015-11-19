#ifndef GUI_DEBUGWINDOW_H
#define GUI_DEBUGWINDOW_H

#include "GUI_Window.h"

struct ImVec2;

namespace id {

class Device;
namespace scene {
class SceneNode;
} // namespace scene

class EditMaterialWindow;

class DebugWindow : public GUI_Window
{
public:
	DebugWindow();
	~DebugWindow();
	
	auto Display(Device* dev) 	-> void;
	auto Display() 				-> void;
	
private:
	auto DisplayNodesTree(scene::SceneNode* node) -> void;

	EditMaterialWindow* _edit_material_window;
};

} // namespace id

#endif
