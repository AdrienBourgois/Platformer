#ifndef GUI_DEBUGWINDOW_H_INCLUDED
#define GUI_DEBUGWINDOW_H_INCLUDED

#include "guiWindow.h"

struct ImVec2;

namespace id {

class DebugLogger;
class Device;

namespace scene {
	class SceneNode;
} // namespace scene

class EditMaterialWindow;

class DebugWindow 
: public GUI_Window
{
public:
	DebugWindow();
	virtual ~DebugWindow();
	DebugWindow(DebugWindow const&) = delete;
	DebugWindow(DebugWindow&&) = delete;
	auto operator=(DebugWindow const&) -> DebugWindow& = delete;
	auto operator=(DebugWindow&&) -> DebugWindow& = delete;
	
	auto Display(Device* dev) 	-> void;
	auto Display() 				-> void;
	
private:
	auto DisplayNodesTree(scene::SceneNode* node) -> void;

	EditMaterialWindow* _edit_material_window;
	DebugLogger*	_guiLogger;
};

} // namespace id

#endif // GUI_DEBUG_WINDOW_H_INCLUDED
