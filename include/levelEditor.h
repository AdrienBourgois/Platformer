#ifndef LEVEL_EDITOR_H_INCLUDED
#define LEVEL_EDITOR_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "logger.h"
#include "guiWindow.h"
#include "device.h"

namespace id {

class MenuLevelEditor;

class LevelEditor
{
public:
	LevelEditor(Device* dev);
	~LevelEditor();
	LevelEditor(LevelEditor const&) = delete;
	auto operator=(LevelEditor const&) = delete;

	auto InitLevelEditor() -> void;	
	auto DisplayLevelEditor() -> void;
	auto UpdateLevelEditor() -> void;
		
private:
//	bool	visible;
	Device*			dev;
	MenuLevelEditor*	menuLevelEditor;	
};

}//End id

#endif
