#ifndef GUI_OPEN_FILE_H_INCLUDED
#define GUI_OPEN_FILE_H_INCLUDED

#include <string>
#include "guiWindow.h"

namespace id {

class Device;

namespace scene {
	class SceneNode;
} // namespace scene

class OpenFile 
: public GUI_Window
{
public:
	OpenFile();
	virtual ~OpenFile() = default;
	OpenFile(OpenFile const&) = delete;
	OpenFile(OpenFile&&) = delete;
	auto operator=(OpenFile const&) -> OpenFile& = delete;
	auto operator=(OpenFile&&) -> OpenFile& = delete;
	
	auto Display(Device* dev) -> void;
	auto DisplayLoadLevel(Device* dev) -> void;
	auto DisplayMenuAdd(Device* dev) -> void;
	auto DisplayDirTreeLoadLevel(Device* dev, int type, std::string path, bool force) -> void;
	
	auto getLoadMenu() const -> bool 	{ return loadMenu; 	}
	auto getAddMenu() const -> bool 	{ return addMenu; 	}		
	auto setAddMenu(bool act) -> void 	{ addMenu = act; 	}
	auto setLoadMenu(bool act2) ->void 	{ loadMenu = act2;	}

private:
    auto DisplayDirTree(Device* dev, int type, std::string path, bool force) -> void;
	bool loadMenu;
	bool addMenu;
	std::string fileNameSave;
};

} // namespace id

#endif // GUI_OPEN_FILE_H_INCLUDED

