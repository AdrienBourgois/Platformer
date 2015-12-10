#ifndef MENUASSETSLEVELEDITOR_H_INCLUDED
#define MENUASSETSLEVELEDITOR_H_INCLUDED

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
	~MenuAssetsLevelEditor();

	auto getActive() const -> bool {return active;}
	auto setActive(bool act) -> void {active = act;}
		
	virtual auto Display() -> void override;	
	virtual	auto Display(Device* dev) -> void override;

private:
	auto DisplayNodesTreeLevelEditor(scene::SceneNode* node) ->void;
	bool active;
};


}//end

#endif
