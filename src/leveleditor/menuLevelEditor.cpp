#include "SDL2/SDL.h"
#include "leveleditor/menuLevelEditor.h"
#include "logger.h"
#include "json/jsonWriter.h"
#include "sceneManager.h"
#include "guiOpenFile.h"
#include "guiSaveFile.h"

namespace id {

MenuLevelEditor::MenuLevelEditor(Device* device)
: LevelEditorElement(device)
{
	LOG(L_INFO, "Creating MenuLevelEditor");

	openfile = new (std::nothrow) OpenFile();
	savefile = new (std::nothrow) SaveFile();
	SDL_assert(openfile);
	SDL_assert(savefile);
	LOG(L_INFO, "Creating MenuLevelEditor Finish");
}

MenuLevelEditor::~MenuLevelEditor()
{
	LOG(L_INFO, "Destructing MenuLevelEditor");
	
	LOG(L_INFO, "Destructing MenuLevelEditor Finish");
}

auto MenuLevelEditor::Display() -> void 
{
	
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("New Level"))
			{
				std::cout<< "New Level" << std::endl;
			}
	
			if(ImGui::MenuItem("Save Level"))
			{
				savefile->setActiveSave(true);
			}
	
			if(ImGui::MenuItem("Load Level"))
			{
				openfile->setActive(true);
			}
			
			if(ImGui::MenuItem("Exit"))
			{
				std::cout<< "Exit" << std::endl;
			}
			ImGui::EndMenu();
		}
	
		if(ImGui::BeginMenu("Create"))
		{
			if(ImGui::BeginMenu("Entity"))
			{
				if(ImGui::MenuItem("Player", "Create spawn player"))
				{}
				if(ImGui::MenuItem("Enemy", "Create spawn eneny"))
				{}			
				ImGui::EndMenu();
			}
			if(ImGui::BeginMenu("Plateform"))
			{
				if(ImGui::MenuItem("Create cube","Create cube plateform"))
				{}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}	
			
		if(ImGui::BeginMenu("Assets"))
		{
		ImGui::EndMenu();
		}
		
		if(ImGui::BeginMenu("Transform"))
		{
		ImGui::EndMenu();	
		}

	ImGui::EndMainMenuBar();
	}
		if(openfile->getActive())		
			openfile->DisplayLoadLevel(dev);	
		if(savefile->getActiveSave())		
			savefile->DisplaySaveLevel(dev);	
}

auto MenuLevelEditor::Update() -> void
{
}

}//end id 
