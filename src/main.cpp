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
#include "enemy.h"
#include "pathEnemy.h"
#include "player.h"
#include "guiMenu.h"
#include "txtLogger.h"
#include "json/jsonWriter.h"
#include "json/jsonReader.h"
#include "guiLifeBar.h"
#include "eventManager.h"
#include "eventReceiver.h"
#include "eventPlayer.h"
#include "eventCamera.h"

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

	id::scene::Player * player = id::scene::Player::createPlayer(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Player", "pos3d_tex2d", "assets/Robot.obj"); // player creation

	id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});

	float last = 0.f;
	float deltaTime = 0.f;
	float now = SDL_GetTicks();

	if (now > last)
	{	
		deltaTime = (now-last) / 1000.f;
		last = now;
	}

//	id::json::JsonWriter jsonWriter;
//	jsonWriter.saveDefaultBindKey();
//	jsonWriter.saveDefaultResolution();

	id::DebugLogger* debug_logger = new (std::nothrow) id::DebugLogger;	
	id::DebugWindow* debug_window = new (std::nothrow) id::DebugWindow();
	id::OpenFile* open_file = new (std::nothrow) id::OpenFile();
	
	id::Device* dev = device.get();
	std::function<void()> funcQuit = [dev]() {dev->close();};
	device->getGui()->addMenuTitleScreen(funcQuit);

	id::gui::GuiLifeBar* life = new id::gui::GuiLifeBar(device->getGui(), 300);
	float damage = 0.1f;

	device->getGui()->addMenuTitleScreen(funcQuit);

	id::event::EventPlayer* evtPlayer = new id::event::EventPlayer(device.get(), "EventPlayer", player);
	id::event::EventCamera* evtCam = new id::event::EventCamera(device.get(), "EventCam", cam);
	device->getEventManager()->addEventReceiver(evtPlayer);
	device->getEventManager()->addEventReceiver(evtCam);
	device->getEventManager()->useEventReceiver("EventCam");

	while (device->run())
	{
		device->setDeltaTime(deltaTime);
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		id::imgui_impl::NewFrame(device.get());
	
		debug_logger->DisplayLog();	
		debug_window->Display(device.get());
		open_file->Display(device.get());
		
		device->getGui()->render();
		#ifdef _DEBUG
			ImGui::Render();
		#endif

		life->refreshLifeBar(damage);

		device->getWindow()->swap();
	}
	ImGui::Shutdown();
	delete life;
	delete debug_logger;	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
