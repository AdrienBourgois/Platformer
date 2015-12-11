#ifndef GUI_CHANGE_TEXTURE_GROUP_WINDOW_H_INCLUDED
#define GUI_CHANGE_TEXTURE_GROUP_WINDOW_H_INCLUDED

#include "guiWindow.h"

namespace id {

class Material;
class mtl;

class ChangeTextureGroupWindow 
: public GUI_Window
{
public:
	ChangeTextureGroupWindow();
	virtual ~ChangeTextureGroupWindow() = default;
	ChangeTextureGroupWindow(ChangeTextureGroupWindow const&) = delete;
	ChangeTextureGroupWindow(ChangeTextureGroupWindow&&) = delete;
	auto operator=(ChangeTextureGroupWindow const&) -> ChangeTextureGroupWindow& = delete;
	auto operator=(ChangeTextureGroupWindow&&) -> ChangeTextureGroupWindow& = delete;

	auto Display() -> void;
	
	auto setActiveMaterial(Material* material) 	-> void 		{ _active_material = material; 	}
	auto getActiveMaterial() const				-> Material* 	{ return _active_material; 		}
	
	auto setActiveMtl(mtl* _mtl) 				-> void 		{ _active_mtl = _mtl; 			}
	auto getActiveMtl() const					-> mtl* 		{ return _active_mtl; 			}

private:
	Material* 	_active_material;
	mtl* 		_active_mtl;

	auto DisplayDirTree(int type, std::string path, bool force) -> void;
};

} // namespace id

#endif // GUI_CHANGE_TEXTURE_GROUP_WINDOW_H_INCLUDED
