#ifndef GUI_EDIT_SHADER_H_INCLUDED
#define GUI_EDIT_SHADER_H_INCLUDED

#include <string>
#include "guiWindow.h"

namespace id {

class Device;

namespace scene {
	class SceneNode;
} // namespace scene

class EditShader
: public GUI_Window
{
public:
	EditShader(std::string current_shader);
	virtual ~EditShader() = default;
	EditShader(EditShader const&) = delete;
	EditShader(EditShader&&) = delete;
	auto operator=(EditShader const&) -> EditShader& = delete;
	auto operator=(EditShader&&) -> EditShader& = delete;

    auto Display(Device* dev) 					-> void;
	auto setCurrentShader(std::string shader) 	-> void { current_shader = shader; }

private:
	std::string 	current_shader;
	int				_selec_shader;
};

} // namespace id

#endif // GUI_EDIT_SHADER_H_INCLUDED
