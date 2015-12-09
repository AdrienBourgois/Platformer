#include "SDL2/SDL.h"
#include "leveleditor/menuLevelEditor.h"
#include "logger.h"
<<<<<<< HEAD
#include "json/jsonWriter.h"
#include "json/jsonReader.h"
#include "sceneManager.h"
=======
#include "guiOpenFile.h"
>>>>>>> leveleditor2

namespace id {

MenuLevelEditor::MenuLevelEditor(Device* device)
: LevelEditorElement(device)
{
	LOG(L_INFO, "Creating MenuLevelEditor");

	openfile = new (std::nothrow) OpenFile();
	SDL_assert(openfile);
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
				json::JsonWriter jsonWriter;
				jsonWriter.writeAllNode(dev->getSceneManager()->getRootNode(), "myLevel1");
			}
	
			if(ImGui::MenuItem("Load Level"))
			{
				openfile->setActive(true);
			//	json::JsonReader jsonReader;
			//	jsonReader.loadAllNode(dev, "myLevel1");
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
}

auto MenuLevelEditor::Update() -> void
{
}

}//end id 
