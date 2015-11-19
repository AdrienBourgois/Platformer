#include <SDL2/SDL.h>
#include "GUI_OpenFile.h"
#include "MeshSceneNode.h"
#include "imgui_impl.h"
#include "Window.h"
#include <iostream>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include "FileUtility.h"
#include "LoadFromJson.h"


namespace id {

OpenFile::OpenFile()
: GUI_Window(true)
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
			ImGui::Selectable(("   " + file_name).c_str(), &selec);
			if (selec)
				JsonLoad::loadFromJson(file_name, dev->getSceneManager());		
		}
	}
}

} // namespace id
