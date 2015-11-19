#include <SDL2/SDL.h>
#include "GUI_EditShader.h"
#include "imgui_impl.h"
#include <iostream>
#include "Shaders.h"
#include "Driver.h"

namespace id {

EditShader::EditShader(std::string current_shader)
: GUI_Window(false), current_shader(current_shader)
{
	_selec_shader = 0;
}

void EditShader::Display(Device* dev)
{
	SDL_assert(dev);

	if (_visible)
	{
		Shaders* shader = dev->getDriver()->getShader();
		(void)shader;
		std::string window_title = "Edit Shader " + current_shader;
		
		ImGui::SetNextWindowSize({200,200}, ImGuiSetCond_FirstUseEver);
		
		ImGui::Begin(window_title.c_str(), &_visible);
		
		ImGui::RadioButton("Vertex", &_selec_shader, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Fragment", &_selec_shader, 1);
		
		char* shader_data = (char*)"ERROR!";
		int size = 7;
		if (_selec_shader == 0) // Vertex
		{
			shader_data = &shader->getShaderData(current_shader)->vertex[0];
			size = shader->getShaderData(current_shader)->vertex.size();
		}
		else if (_selec_shader == 1) // Fragment
		{
			shader_data = &shader->getShaderData(current_shader)->fragment[0];
			size = shader->getShaderData(current_shader)->fragment.size();
		}
		ImGui::InputTextMultiline("##source", shader_data, size, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput);
		
		//if (ImGui::Button("Compile"))
		//{
		//	
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Save"))
		//{
		//	
		//}
		ImGui::End();
	}
}
} // namespace id
