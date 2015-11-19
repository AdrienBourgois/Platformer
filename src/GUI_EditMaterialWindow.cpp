#include <SDL2/SDL.h>
#include "GUI_EditMaterialWindow.h"
#include "imgui_impl.h"
#include <iostream>
#include "MeshSceneNode.h"
#include "Driver.h"
#include "Shaders.h"
#include "Mesh.h"
#include "GUI_ChangeTextureGroupWindow.h"
#include "GUI_EditShader.h"

namespace id {


EditMaterialWindow::EditMaterialWindow()
: GUI_Window(false)
{
	_active_node = nullptr;
	_change_texture_group_window = new ChangeTextureGroupWindow();
	_edit_shader_window = new EditShader("");
	_shader_list = {"pos3d_color4",
					"pos3d_color4_normal",
					"pos3d",
					"pos3d_normal",
					"pos3d_tex2d",
					"pos3d_tex2d_normal",
					"simple"};

}

EditMaterialWindow::~EditMaterialWindow()
{
	delete _edit_shader_window;
	delete _change_texture_group_window;
}

auto EditMaterialWindow::Display(Device* dev) -> void
{
	SDL_assert(dev);

	if (_visible)
	{
		if (!_change_texture_group_window)
			_change_texture_group_window = new ChangeTextureGroupWindow();
		_change_texture_group_window->Display();
		if (!_edit_shader_window)
			_edit_shader_window = new EditShader("");
		_edit_shader_window->Display(dev);
		std::string title = "Edit material [" + _active_node->getName() + "]";
		ImGui::Begin(title.c_str(), NULL, {300, 300});
		if (ImGui::TreeNode("Change shader"))
		{
			for (std::string shader_name : _shader_list)
			{
				_active_node->getScene()->getDriver()->getShader()->loadProgram(shader_name);
				unsigned int prg_id = _active_node->getScene()->getDriver()->getShader()->getPrg(shader_name);
				bool selec = ((scene::MeshSceneNode*)(_active_node))->getPrgId() == prg_id;
				ImGui::Selectable(shader_name.c_str(), &selec, 0, {170,0});
				if (selec)
				{
					((scene::MeshSceneNode*)(_active_node))->setPrgId(prg_id);
				}
				ImGui::SameLine();
				std::string edit_button_label = "Edit##" + shader_name;
				if (ImGui::SmallButton(edit_button_label.c_str()))
				{
					_edit_shader_window->setVisible(true);
					_edit_shader_window->setCurrentShader(shader_name);
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Change texture"))
		{
			Material* material = ((scene::MeshSceneNode*)_active_node)->getMesh()->getMaterial();
			for (auto material_mtl : material->getMTLs())
			{
				bool selec = false;
				std::string selectable_text = material_mtl.first + " [" + material_mtl.second.map_Kd + "]";
				ImGui::Selectable(selectable_text.c_str(), &selec);
				if (selec && (material_mtl.second.map_Kd != ""))
				{
					_change_texture_group_window->setActiveMtl(material->getMTL(material_mtl.second.name));
					_change_texture_group_window->setActiveMaterial(material);
					_change_texture_group_window->setVisible(true);
				}
			}

			ImGui::TreePop();
		}
		ImGui::End();
	}
	else
	{
		_change_texture_group_window->setVisible(false);
	}
}

} // namespace id
