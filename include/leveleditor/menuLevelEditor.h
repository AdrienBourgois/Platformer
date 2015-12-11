#ifndef MENU_LEVEL_EDITOR_H_INCLUDED
#define MENU_LEVEL_EDITOR_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "guiWindow.h"
#include "leveleditor/levelEditorElement.h"

namespace id {

class MenuAssetsLevelEditor;

class OpenFile;
class SaveFile;

class MenuLevelEditor
: public LevelEditorElement
{
public:
	MenuLevelEditor(Device* dev);
	virtual ~MenuLevelEditor();
	MenuLevelEditor(MenuLevelEditor const&) = delete;
	MenuLevelEditor(MenuLevelEditor&&) = delete;
	auto operator=(MenuLevelEditor const&) -> MenuLevelEditor& = delete;
	auto operator=(MenuLevelEditor&&) -> MenuLevelEditor& = delete;	

	auto Display() -> void override;
	auto Display(Device* dev) -> void override;
	auto Update() -> void;

private:
	OpenFile* openfile;
	MenuAssetsLevelEditor* menuAssets;	
	SaveFile* savefile;
};


} // namespace id 

#endif // MENU_LEVEL_EDITOR_H_INCLUDED
