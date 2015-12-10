#ifndef GUI_OPEN_FILE_H_INCLUDED
#define GUI_OPEN_FILE_H_INCLUDED

#include <string>
#include "guiWindow.h"

namespace id {

class Device;
namespace scene {
class SceneNode;
} // namespace scene

class OpenFile : public GUI_Window
{
public:
	OpenFile();
	~OpenFile() = default;
	
	auto Display(Device* dev) -> void;
	auto DisplayLoadLevel(Device* dev) -> void;
	auto DisplaySaveLevel(Device* dev) -> void;
	auto DisplayDirTreeLoadLevel(Device* dev, int type, std::string path, bool force) -> void;
	
	auto getActive() const -> bool {return active;}	
	auto setActive(bool act) -> void {active = act;}
	
	auto getActiveSave() const -> bool {return activeSave;}	
	auto setActiveSave(bool act) -> void {activeSave = act;}

	
private:
    auto DisplayDirTree(Device* dev, int type, std::string path, bool force) -> void;
	bool active;
	bool activeSave;
	std::string fileNameSave;
};

} // namespace id

#endif // GUI_OPEN_FILE_H_INCLUDED

