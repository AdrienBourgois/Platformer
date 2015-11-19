#ifndef GUI_EDIT_SHADER_H
#define GUI_EDIT_SHADER_H

#include <string>
#include "imgui_impl.h"
#include "GUI_Window.h"

namespace id {

class Device;
namespace scene {
class SceneNode;
} // namespace scene

class EditShader : public GUI_Window
{
public:
	EditShader(std::string current_shader);
	~EditShader() = default;

    auto Display(Device* dev) 					-> void;
	
	auto setCurrentShader(std::string shader) 	-> void { current_shader = shader; }

private:
	std::string 	current_shader;
	int				_selec_shader;
};

} // namespace id

#endif
