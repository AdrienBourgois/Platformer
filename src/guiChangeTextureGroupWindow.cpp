#include <dirent.h>
#include <iostream>
#include <string>

#include "material.h"
#include "fileUtility.h"
#include "guiChangeTextureGroupWindow.h"
#include "imgui_impl.h"
#include "texture.h"

namespace id {

ChangeTextureGroupWindow::ChangeTextureGroupWindow()
: GUI_Window(false)
{
	
}

auto ChangeTextureGroupWindow::Display() -> void
{
	if (_visible)
	{
		std::string title = "Select a texture file for ";
		if (_active_mtl)
			title += _active_mtl->name;
		
		ImGui::Begin(title.c_str(), &_visible);
		ImGui::SetNextTreeNodeOpened(true);

		this->DisplayDirTree(4, "./assets", true);

		ImGui::End();
	}
}

auto ChangeTextureGroupWindow::DisplayDirTree(int type, std::string path, bool force = false) -> void
{
    std::string file_name = FileUtility::getFileNameFromPath(path);
	std::string file_name_ext = FileUtility::getExtensionFromFileName(file_name);
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
                    ChangeTextureGroupWindow::DisplayDirTree(content.second, path + "/" + content.first);
                closedir(dir);
                ImGui::TreePop();
            }
        }
		else if (type == 8 && (file_name_ext == "png")) // Is a file
        {
            bool selec = false;
            ImGui::Selectable(("   " + file_name).c_str(), &selec);
            if (selec)
            {
				auto* texture = Texture::addTexture(path);
				if (!texture->load())
						
		_active_material->setTexture(_active_mtl->name, file_name, texture);
            }
        }
    }
}

} // namespace id
