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
	LevelEditor(LevelEditor&&) = delete;
	auto operator=(LevelEditor const&) = delete;
	auto operator=(LevelEditor&&) = delete;

	auto getActive() const -> bool {return activeLevelEditor;}
	auto setActive(bool act) -> void {activeLevelEditor = act;}

	auto InitLevelEditor() -> void;	
	auto DisplayLevelEditor() -> void;
	auto UpdateLevelEditor() -> void;
		
private:
	Device*			dev;
	MenuLevelEditor*	menuLevelEditor;
	bool			activeLevelEditor;
};

} // namespace id

#endif // LEVEL_EDITOR_H_INCLUDED
