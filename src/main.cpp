
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
#include "json/jsonObject.h"
#include "json/jsonArray.h"
#include "json/jsonString.h"
#include "json/jsonNumber.h"
#include "json/jsonBool.h"
#include "json/jsonNull.h"
#include "json/jsonValue.h"
#include "json/jsonReader.h"
#include "maths/matrix.h"
#include <string>
#include <iostream>
int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);
/*
	id::json::JsonWriter jsonWriter;

	id::json::JsonObject* obj  = new id::json::JsonObject;
	id::json::JsonObject* objRoot  = new id::json::JsonObject;

	objRoot->addInObject("parent", new id::json::JsonNull);
	objRoot->addInObject("name", new id::json::JsonString("root"));
	id::json::JsonArray* matrixRoot = new id::json::JsonArray;
	for (int i = 0; i < 16; ++i)
	{
		if ( i == 0 || i == 5 || i == 10 || i == 15)
			matrixRoot->addInArray(new id::json::JsonNumber(1));
		else
			matrixRoot->addInArray(new id::json::JsonNumber(0));
	}
	objRoot->addInObject("transformation", matrixRoot);
	id::json::JsonObject* meshRoot = new id::json::JsonObject;
	meshRoot->addInObject("objPath", new id::json::JsonString("./assets/model/Dragon.obj"));
	id::json::JsonObject* materialRoot = new id::json::JsonObject;
	materialRoot->addInObject("texturePath", new id::json::JsonString("./assets/model/dragon.png"));
	meshRoot->addInObject("material", materialRoot);
	objRoot->addInObject("mesh", meshRoot);
	obj->addInObject("root", objRoot);
	jsonWriter.write(obj);

	id::json::JsonValue::deleteAllJsonValue();
*/
	std::unique_ptr<id::Device> device = device->create();

	id::json::JsonReader jsonReader;

	jsonReader.loadAllNode(device.get());
	
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
