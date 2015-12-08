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

	id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "'", "pos3d_tex2d", "./assets/models/Dragon.obj");
	id::scene::MeshSceneNode* mesh_scn1 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "dragon1", "pos3d_tex2d", "./assets/models/Dragon.obj");
	id::scene::MeshSceneNode* mesh_scn2 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), mesh_scn1, "dragon2", "pos3d_tex2d", "./assets/models/Dragon.obj");
	id::scene::MeshSceneNode* mesh_scn3 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), mesh_scn2, "dragon3", "pos3d_tex2d", "./assets/models/Dragon.obj");
	mesh_scn->setPosition({10,10,10});
	mesh_scn1->setPosition({0,10,10});
	mesh_scn2->setPosition({10,-10,10});
	mesh_scn3->setPosition({0,0,10});
	id::json::JsonWriter jsonWriter;
	jsonWriter.writeNode(mesh_scn, "partie1");	
	jsonWriter.saveDefaultBindKey();
	jsonWriter.saveDefaultResolution();
//	if (jsonWriter.checkExistingValue("105"))
//		std::cout << "existing value" << std::endl;
//	else
//		std::cout << "not existing value" << std::endl;
//	jsonWriter.modifyLineByNameSearch("jump", "k");
	id::json::JsonReader jsonReader;

	auto map = jsonReader.loadScreenResolution();
	for (auto&& val : map)
		std::cout << val.first << " : " << val.second << std::endl;

	jsonWriter.modifyLineByValueSearch("1280", "1080", "resolutionScreen");
	jsonWriter.modifyLineByValueSearch("720", "600", "resolutionScreen");
//	jsonWriter.modifyLineByValueSearch("Alt right", "Right Shit");
	
		jsonReader.loadAllNode(device.get());
	map = jsonReader.loadScreenResolution();
	for (auto&& val : map)
		std::cout << val.first << " : " << val.second << std::endl;
//	std::map<std::string, std::string> map = jsonReader.loadKeyBinding();
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
