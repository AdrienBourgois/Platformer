#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>
#include <memory>
#include <string>

#include "device.h"
#include "window.h"
#include "txtLogger.h"
#include "meshSceneNode.h"
#include "cameraSceneNode.h"
#include "imgui.h"
#include "imgui_impl.h"
#include "guiDebugWindow.h"
#include "guiOpenFile.h"
#include "driver.h"
#include "fileUtility.h"
#include "guiManager.h"
#include "guiEventReceiver.h"
#include "logger.h"
#include "guiLogger.h"
#include "maths/utility.h"
#include "event.h"
#include "enemy.h"
#include "player.h"
#include "guiMenu.h"
#include "txtLogger.h"
#include "json/jsonWriter.h"
#include "json/jsonReader.h"
#include "levelEditor.h"

int main(int argc, char* argv[])
{
	id::TXTLogger* logger = id::TXTLogger::getInstance();
	(void)argc;
	(void)argv;

	logger->setLogLevel(id::LL_ALL);

	LOG(L_ERROR, 32, 454,4554754,455454);
	LOG(L_ERROR, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_GAME, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_WARNING, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_LOOP, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_ERROR, "pouet");

	LOG(L_INFO, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_DEBUG, 4432, "dqwedqwdqw",4554754,455454);
	std::unique_ptr<id::Device> device = device->create();


	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;

	}
		id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "cube", "pos3d_tex2d", "");

	id::scene::Enemy * enemy = id::scene::Enemy::createEnemy(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Enemy", "pos3d_tex2d", "assets/models/Dragon.obj"); // enemy creation

	id::scene::Player * player = id::scene::Player::createPlayer(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Player", "pos3d_tex2d", "assets/models/Robot.obj"); // player creation

id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
//	id::scene::MeshSceneNode* mesh_scn2 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), mesh_scn1, "dragon2", "pos3d_tex2d", "./assets/models/Dragon.obj");
//	id::scene::MeshSceneNode* mesh_scn3 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), mesh_scn2, "dragon3", "pos3d_tex2d", "./assets/models/Dragon.obj");
//	mesh_scn->setPosition({10,10,10});
//	mesh_scn1->setPosition({0,10,10});
//	mesh_scn2->setPosition({10,-10,10});
//	mesh_scn3->setPosition({0,0,10});
	id::json::JsonWriter jsonWriter;
//	jsonWriter.saveDefaultBindKey();
//	jsonWriter.saveDefaultResolution();
//	jsonWriter.writeAllNode(device->getSceneManager()->getRootNode(), "partie1");
	id::json::JsonReader jsonReader;
	jsonReader.loadAllNode(device.get());

//	id::json::JsonWriter jsonWriter;
//	jsonWriter.writeNode(mesh_scn);	

//	id::json::JsonReader jsonReader;
//	jsonReader.loadAllNode(device.get());


	id::DebugLogger* debug_logger = new (std::nothrow) id::DebugLogger;	
	id::LevelEditor* level_editor = new (std::nothrow) id::LevelEditor(device.get());
//	level_editor->InitLevelEditor();
	id::DebugWindow* debug_window = new (std::nothrow) id::DebugWindow();
//	id::OpenFile* open_file = new (std::nothrow) id::OpenFile();
	
	id::scene::Event* ev = new id::scene::Event(player, enemy); // Event initialization

	device->getGui()->addMenuTitleScreen();	

	while (device->run())
	{
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		id::imgui_impl::NewFrame(device.get());

		ImGui::ShowTestWindow();	

		debug_logger->DisplayLog();	
		level_editor->DisplayLevelEditor();
		debug_window->Display(device.get());
	//	open_file->Display(device.get());
		
//		device->getGui()->render();
		#ifdef _DEBUG
			ImGui::Render();
		#endif
	
		if (player) // if player was not create create , don't try to use the event
			ev->playerEventReceiver();

		device->getWindow()->swap();
	}
	ImGui::Shutdown();
	delete debug_logger;	
	delete debug_window;
//	delete open_file;
	
	return EXIT_SUCCESS;
}
