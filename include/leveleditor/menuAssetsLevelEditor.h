#ifndef MENU_ASSETS_LEVEL_EDITOR_H_INCLUDED
#define MENU_ASSETS_LEVEL_EDITOR_H_INCLUDED

#include "guiWindow.h"
#include "leveleditor/levelEditorElement.h"

namespace id {

class Device;
namespace scene {
class SceneNode;
}//namespace scene

class MenuAssetsLevelEditor : public LevelEditorElement 
{
public:
	MenuAssetsLevelEditor(Device* dev);
	virtual ~MenuAssetsLevelEditor();
	MenuAssetsLevelEditor(MenuAssetsLevelEditor const&) = delete;
	MenuAssetsLevelEditor(MenuAssetsLevelEditor&&) = delete;
	auto operator=(MenuAssetsLevelEditor const&) -> MenuAssetsLevelEditor& = delete;
	auto operator=(MenuAssetsLevelEditor&&) -> MenuAssetsLevelEditor& = delete;	

	auto getActive() const -> bool 		{ return active; }
	auto setActive(bool act) -> void 	{ active = act;  }
		
	virtual auto Display() -> void override;	
	virtual	auto Display(Device* dev) -> void override;

private:
	auto DisplayNodesTreeLevelEditor(scene::SceneNode* node) ->void;
	bool active;
};


} // namespace id

#endif // MENU_ASSETS_LEVEL_EDITOR_H_INCLUDED
