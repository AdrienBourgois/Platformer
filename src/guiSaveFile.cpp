#include <fstream>

#include "guiSaveFile.h"
#include "device.h"
#include "json/jsonWriter.h"
#include "imgui_impl.h"
#include "sceneManager.h"
#include "logger.h"

namespace id {

SaveFile::SaveFile()
:activeSave(false)
{
	LOG(L_INFO, "Creating SaveFile");
}

auto SaveFile::DisplaySaveLevel(Device* dev) -> void
{
		ImGui::OpenPopup("Save level");
	      	if (ImGui::BeginPopupModal("Save level", NULL, ImGuiWindowFlags_AlwaysAutoResize))
           	{
				std::string displayedFilename = fileNameSave;
				displayedFilename.reserve(fileNameSave.size() + 30);


            	ImGui::InputText("File to save", &displayedFilename[0], displayedFilename.capacity() * sizeof(displayedFilename[0]));

				for (size_t idx = 0; idx < displayedFilename.capacity(); ++idx)
					if (displayedFilename[idx] == '\0')
					{
						displayedFilename.resize(idx);
						break;
					}

				fileNameSave = displayedFilename;

				if (ImGui::Button(("Save"), ImVec2(120,0)))
				{
					json::JsonWriter jsonWriter;
					jsonWriter.writeAllNode(dev->getSceneManager()->getRootNode(), fileNameSave);
				}

			}	
		if (ImGui::Button("Cancel", ImVec2(120,0)))
		{
			activeSave = false;
			 ImGui::CloseCurrentPopup();
		}
                ImGui::EndPopup();
}

} // namespace id
