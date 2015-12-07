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
#include "txtLogger.h"
#include "json/jsonWriter.h"
#include "json/jsonReader.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);

	std::unique_ptr<id::Device> device = device->create();


	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;
	}

	id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "dragon", "pos3d_tex2d", "./assets/models/Dragon.obj");
	mesh_scn->setPosition({10,10,10});
	id::json::JsonWriter jsonWriter;
	
	jsonWriter.writeNode(mesh_scn, "partie1");	

//	id::json::JsonReader jsonReader;

//	jsonReader.loadAllNode(device.get());

	id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
    (void)cam;

	id::DebugWindow* debug_window = new id::DebugWindow();
	id::OpenFile* open_file = new id::OpenFile();

	while (device->run())
	{
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		
		id::imgui_impl::NewFrame(device.get());
		
        debug_window->Display(device.get());
		open_file->Display(device.get());

		ImGui::Render();
		device->getWindow()->swap();
	}

	ImGui::Shutdown();
	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
