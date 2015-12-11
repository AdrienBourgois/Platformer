#ifndef MENULEVELEDITOR_H_INCLUDED
#define MENULEVELEDITOR_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "guiWindow.h"
//#include "leveleditor/levelEditorElement.h"
#include "leveleditor/menuAssetsLevelEditor.h"

namespace id {

class OpenFile;
class SaveFile;

class MenuLevelEditor
: public LevelEditorElement
{
public:
	MenuLevelEditor(Device* dev);
	~MenuLevelEditor();
	
	auto Display() -> void override;
	auto Display(Device* dev) -> void override;
	auto Update() -> void;

private:
	OpenFile* openfile;
	MenuAssetsLevelEditor* menuAssets;	
	SaveFile* savefile;
};


} //end id 
#endif
