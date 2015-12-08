#ifndef LEVEL_EDITOR_H_INCLUDED
#define LEVEL_EDITOR_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "logger.h"
#include "guiWindow.h"

namespace id {

class MenuLevelEditor;

class LevelEditor : public GUI_Window
{
public:
	LevelEditor();
	~LevelEditor();
	LevelEditor(LevelEditor const&) = delete;
	auto operator=(LevelEditor const&) = delete;

	auto InitLevelEditor() -> void;	
	auto DisplayLevelEditor() -> void;
	auto UpdateLevelEditor() -> void;
		
private:
//	bool	visible;
	MenuLevelEditor*	menuLevelEditor;	
};

}//End id

#endif
