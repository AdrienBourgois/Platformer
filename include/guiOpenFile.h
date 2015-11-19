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

private:
    auto DisplayDirTree(Device* dev, int type, std::string path, bool force) -> void;
};

} // namespace id

#endif // GUI_OPEN_FILE_H_INCLUDED
