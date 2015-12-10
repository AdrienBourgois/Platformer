#include <SDL2/SDL.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

#include "guiOpenFile.h"
#include "meshSceneNode.h"
#include "imgui_impl.h"
#include "window.h"
#include "fileUtility.h"
#include "json/jsonReader.h"
#include "json/jsonWriter.h" 

namespace id {

OpenFile::OpenFile()
: GUI_Window(true), active(false), activeSave(false) 
{
}

auto OpenFile::Display(Device* dev) -> void
{
	SDL_assert(dev);

	if (_visible)
	{
		float height = dev->getWindow()->getHeight();
		float width  = dev->getWindow()->getWidth();
		ImGui::SetNextWindowPos({width*3/4, height*1/10}, 2);

		ImGui::Begin("File Open", NULL, {width * 1/4, height*1/3});
		ImGui::SetNextTreeNodeOpened(true);

		DisplayDirTree(dev, 4, ".", true);

		ImGui::End();
	}
}

auto OpenFile::DisplayLoadLevel(Device* dev) -> void
{
	SDL_assert(dev);
	
	if (_visible)
	{
		ImGui::OpenPopup("Load level");
	      	if (ImGui::BeginPopupModal("Load level", NULL, ImGuiWindowFlags_AlwaysAutoResize))
           	{
			DisplayDirTreeLoadLevel(dev, 4, ".", true);
		
		if (ImGui::Button("Cancel", ImVec2(120,0)))
		{
			setActive(false);
			 ImGui::CloseCurrentPopup();
		}
                ImGui::EndPopup();
		}
	}
}

auto OpenFile::DisplaySaveLevel(Device* dev) -> void
{
	SDL_assert(dev);
	(void)dev;	
	if (_visible)
	{
		ImGui::OpenPopup("Save level");
	      	if (ImGui::BeginPopupModal("Save level", NULL, ImGuiWindowFlags_AlwaysAutoResize))
           	{
				fileNameSave.resize(fileNameSave.size() + 32);
				std::cout << fileNameSave.size() << std::endl;
            	ImGui::InputText("File to save", &fileNameSave[0], fileNameSave.size() * sizeof(fileNameSave[0]));
				if (ImGui::Button(("Save"), ImVec2(120,0)))
				{
					json::JsonWriter jsonWriter;
					jsonWriter.writeAllNode(dev->getSceneManager()->getRootNode(), fileNameSave);
				}

		
			}	
		if (ImGui::Button("Cancel", ImVec2(120,0)))
		{
			setActiveSave(false);
			 ImGui::CloseCurrentPopup();
		}
                ImGui::EndPopup();
		}
	
}

auto OpenFile::DisplayDirTree(Device* dev, int type, std::string path, bool force = false) -> void
{
	SDL_assert(dev);

	std::string file_name = FileUtility::getFileNameFromPath(path);
	if ((file_name != "." && file_name != ".." && file_name[0] != '.') || force)
	{
		if (type == 4) // Is a directory
		{
			if (ImGui::TreeNode(file_name.c_str(), "%s", file_name.c_str()))
			{
				std::map<std::string, int> dir_content;
				auto* dir = opendir(path.c_str());
				dirent* dp;
				while ((dp = readdir(dir)) != NULL)
				{
					dir_content[std::string(dp->d_name)] = dp->d_type;
				}
				//std::sort(dir_content.begin(), dir_content.end());
				for (auto const& content : dir_content)
					OpenFile::DisplayDirTree(dev, content.second, path + "/" + content.first);
				closedir(dir);
				ImGui::TreePop();
			}
		}
		else if (type == 8 && (FileUtility::getExtensionFromFileName(file_name) == "obj")) // Is a file
		{
			bool selec = false;
			ImGui::Selectable(("   " + file_name).c_str(), &selec);
			if (selec)
			{
				auto* smgr = dev->getSceneManager();
				id::scene::MeshSceneNode::createMeshSceneNode(smgr, smgr->getRootNode(), file_name, "pos3d_tex2d", path.c_str());
			}
		}
		else if (type == 8 && (FileUtility::getExtensionFromFileName(file_name) == "json")) // is a json save
		{

			bool selec = false;
			std::string buffer = FileUtility::getFileNameWithoutExtension(file_name);
			ImGui::Selectable(("   " + file_name).c_str(), &selec);
			if (selec)
			{
				json::JsonReader jsonReader;
				jsonReader.loadAllNode(dev, buffer);
			}
		}

	}
}

auto OpenFile::DisplayDirTreeLoadLevel(Device* dev, int type, std::string path, bool force = false) -> void
{
	SDL_assert(dev);

	std::string file_name = FileUtility::getFileNameFromPath(path);
	if ((file_name != "." && file_name != ".." && file_name[0] != '.') || force)
	{
		if (type == 4) // Is a directory
		{
			if (ImGui::TreeNode(file_name.c_str(), "%s", file_name.c_str()))
			{
				std::map<std::string, int> dir_content;
				auto* dir = opendir(path.c_str());
				dirent* dp;
				while ((dp = readdir(dir)) != NULL)
				{
					dir_content[std::string(dp->d_name)] = dp->d_type;
				}
				//std::sort(dir_content.begin(), dir_content.end());
				for (auto const& content : dir_content)
					OpenFile::DisplayDirTree(dev, content.second, path + "/" + content.first);
				closedir(dir);
				ImGui::TreePop();
			}
		}
				
	}
}

} // namespace id
