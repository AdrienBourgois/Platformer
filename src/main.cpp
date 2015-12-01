/*
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
*/

#include "txtLogger.h"
#include "json/jsonWriter.h"
#include "json/jsonObject.h"
#include "json/jsonArray.h"
#include "json/jsonString.h"
#include "json/jsonNumber.h"
#include "json/jsonBool.h"
#include "json/jsonNull.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);

	id::json::JsonWriter jsonWriter;

	id::json::JsonObject* obj  = new id::json::JsonObject;
	id::json::JsonObject* obj1 = new id::json::JsonObject;
	id::json::JsonArray*  arr  = new id::json::JsonArray;
	
	arr->addInArray(new id::json::JsonNumber(5));
	arr->addInArray(new id::json::JsonNumber(1224));
	arr->addInArray(new id::json::JsonString("mon tableau"));
	arr->addInArray(new id::json::JsonBool(false));

	obj1->addInObject("id", new id::json::JsonNumber(-1));
	obj1->addInObject("name", new id::json::JsonString("Jojo"));

	arr->addInArray(obj1);
	arr->addInArray(new id::json::JsonNumber(124));
	arr->addInArray(new id::json::JsonNumber(12524));
	arr->addInArray(new id::json::JsonNumber(1864));

	obj1->addInObject("array", arr);
	obj->addInObject("visible", new id::json::JsonBool(true));
	obj->addInObject("obj1", obj1);
	obj->addInObject("pointer", new id::json::JsonNull());

	jsonWriter.write(obj);


/*
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
*/	
	return EXIT_SUCCESS;
}
