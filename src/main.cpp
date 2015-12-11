#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>
#include <memory>
#include <string>

#include "cameraSceneNode.h"
#include "device.h"
#include "driver.h"
#include "enemy.h"
#include "eventCamera.h"
#include "eventManager.h"
#include "eventPlayer.h"
#include "eventReceiver.h"
#include "fileUtility.h"
#include "guiDebugWindow.h"
#include "guiEventReceiver.h"
#include "guiLifeBar.h"
#include "guiLogger.h"
#include "guiManager.h"
#include "guiMenu.h"
#include "guiOpenFile.h"
#include "imgui.h"
#include "imgui_impl.h"
#include "json/jsonReader.h"
#include "json/jsonWriter.h"
#include "logger.h"
#include "maths/utility.h"
#include "meshSceneNode.h"
#include "pathEnemy.h"
#include "player.h"
#include "txtLogger.h"
#include "window.h"

int main(int, char*[])
{
	LOG(L_INFO,"Begin Main");
	id::TXTLogger* logger = id::TXTLogger::getInstance();

	logger->setLogLevel(id::LL_ALL);

	id::json::JsonWriter jsonWriter;
	jsonWriter.saveDefaultBindKey();
	jsonWriter.saveDefaultResolution();

	std::unique_ptr<id::Device> device = device->create();


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

	id::Device* dev = device.get();
	std::function<void()> funcQuit = [dev]() {dev->close();};
	device->getGui()->addMenuTitleScreen(funcQuit);

	id::gui::GuiLifeBar* life = new id::gui::GuiLifeBar(device->getGui(), 300);
	float damage = 0.1f;

	device->getGui()->addMenuTitleScreen(funcQuit);

	id::event::EventPlayer* evtPlayer = new id::event::EventPlayer(device.get(), "EventPlayer", nullptr);
	id::event::EventCamera* evtCam = new id::event::EventCamera(device.get(), "EventCam", cam);
	device->getEventManager()->addEventReceiver(evtPlayer);
	device->getEventManager()->addEventReceiver(evtCam);

	while (device->run())
	{
		device->setDeltaTime(deltaTime);
		device->getDriver()->clear();
		device->getSceneManager()->draw();
	
		device->getGui()->render();
		ImGui::Render();
	
		life->refreshLifeBar(damage);

		device->getWindow()->swap();
	}
	ImGui::Shutdown();

	delete life;
	
	return EXIT_SUCCESS;
}
