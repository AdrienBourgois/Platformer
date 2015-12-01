#include <SDL2/SDL_ttf.h>
#include <typeinfo>
#include <new>

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

int main(int argc, char* argv[])
{
	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);

	std::unique_ptr<id::Device> device = device->create();
	
	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;
	}

	id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
    (void)cam;

	id::DebugWindow* debug_window = new id::DebugWindow();
	id::OpenFile* open_file = new id::OpenFile();

	device->getGui()->addRect(nullptr, 100, 100, 50, 50, 1, true, {1.f, 1.f, 1.f, 1.f});
	device->getGui()->addButton(nullptr, 0, 0, 100, 100, 2, true, {0.f, 0.f, 0.f, 1.f}, "Button", {1.f, 1.f, 1.f, 1.f});
	//device->getGui()->addRect(nullptr, 0, 0, 100, 100, 3, true, {0.f, 0.f, 0.f, 1.f});
	device->getGui()->addStaticText(nullptr, -300, 0, 150, 100, 4, true, "Static text", {0.6f, 0.2f, 0.4f, 1.f});

	while (device->run())
	{
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		
		id::imgui_impl::NewFrame(device.get());

		debug_window->Display(device.get());
		open_file->Display(device.get());

		ImGui::Render();
		device->getGui()->render();
		device->getWindow()->swap();
	}
	ImGui::Shutdown();
	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
