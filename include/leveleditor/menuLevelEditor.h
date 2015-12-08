#ifndef MENULEVELEDITOR_H_INCLUDED
#define MENULEVELEDITOR_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "guiWindow.h"

namespace id {

class MenuLevelEditor : public GUI_Window
{
public:
	MenuLevelEditor();
	~MenuLevelEditor();
	
	auto Display() -> void;
	auto Update() -> void;

private:
};


} //end id 
#endif
