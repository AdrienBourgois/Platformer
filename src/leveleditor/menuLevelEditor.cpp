#include "SDL2/SDL.h"
#include "leveleditor/menuLevelEditor.h"
#include "logger.h"
#include "json/jsonWriter.h"
#include "sceneManager.h"
#include "guiOpenFile.h"
#include "guiSaveFile.h"
#include "player.h"
#include "enemy.h"

namespace id {

MenuLevelEditor::MenuLevelEditor(Device* device)
: LevelEditorElement(device)
{
	LOG(L_INFO, "Creating MenuLevelEditor");

	openfile = new (std::nothrow) OpenFile();
	savefile = new (std::nothrow) SaveFile();
	SDL_assert(openfile);
	menuAssets = new (std::nothrow) MenuAssetsLevelEditor(device);
	SDL_assert(menuAssets);
	SDL_assert(savefile);
	LOG(L_INFO, "Creating MenuLevelEditor Finish");
}

MenuLevelEditor::~MenuLevelEditor()
{
	LOG(L_INFO, "Destructing MenuLevelEditor");
	
	LOG(L_INFO, "Destructing MenuLevelEditor Finish");
}
auto MenuLevelEditor::Display(Device* dev) ->void 
{
(void)dev;
}

auto MenuLevelEditor::Display() -> void 
{
	
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("New Level"))
			{
				dev->getSceneManager()->clearAllNodeExceptRootCam(dev->getSceneManager()->getRootNode());
			}
	
			if(ImGui::MenuItem("Save Level"))
			{
				savefile->setActiveSave(true);
			}
	
			if(ImGui::MenuItem("Load Level"))
			{
				openfile->setLoadMenu(true);
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
				{
					id::scene::Player::createPlayer(dev, dev->getSceneManager(), dev->getSceneManager()->getRootNode(), "Player", "pos3d_tex2d", "./assets/models/Robot.obj");
				}
				if(ImGui::MenuItem("Enemy", "Create spawn eneny"))
				{
					id::scene::Enemy::createEnemy(dev->getSceneManager(), dev->getSceneManager()->getRootNode(), "Enemy0", "pos3d_tex2d", "./assets/models/Dragon.obj");
				}			
				ImGui::EndMenu();
			}
			if(ImGui::BeginMenu("Plateform"))
			{
				if(ImGui::MenuItem("Create cube","Create cube plateform"))
				{
				openfile->setAddMenu(true);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}	
			
		if(ImGui::BeginMenu("Assets"))
		{
			menuAssets->setActive(true);
			ImGui::EndMenu();
		}
		
		if(ImGui::BeginMenu("Transform"))
		{
		ImGui::EndMenu();	
		}

	ImGui::EndMainMenuBar();
	}
		if(openfile->getLoadMenu())		
			openfile->DisplayLoadLevel(dev);
		if(openfile->getAddMenu())
			openfile->DisplayMenuAdd(dev);
		if(menuAssets->getActive())
			menuAssets->Display(dev);	
		if(savefile->getActiveSave())		
			savefile->DisplaySaveLevel(dev);	
}

auto MenuLevelEditor::Update() -> void
{
}

}//end id 
