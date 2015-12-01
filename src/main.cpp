#include <typeinfo>
#include <memory>

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
#include "logger.h"
#include "guiLogger.h"

int main(int argc, char* argv[])
{
	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);
//	id::TXTLogger::getInstance()->
//	int jesus = 57444;
//	(void)debug_logger;
	LOG(L_ERROR, 32, 454,4554754,455454);

	LOG(L_ERROR, 4432, "dqwedqwdqw",4554754,455454);
	LOG(L_ERROR, "pouet");
	std::unique_ptr<id::Device> device = device->create();
	
//	id::DebugLogger* debug_logger = new id::DebugLogger;	
//	std::cout << __FILE__ << std::endl;	
	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;
	}

	id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
    (void)cam;

//	id::DebugWindow* debug_window = new id::DebugWindow();
//	id::OpenFile* open_file = new id::OpenFile();

	id::DebugLogger* debug_logger = new (std::nothrow) id::DebugLogger;	
	bool visible2 = true;	
	while (device->run())
	{
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		id::imgui_impl::NewFrame(device.get());
		
		ImGui::ShowTestWindow(&visible2);
//		debug_window->Display(device.get());
//		open_file->Display(device.get());
		
		debug_logger->DisplayLog();	
		#ifdef _DEBUG
			ImGui::Render();
		#endif
		device->getWindow()->swap();
	}

	ImGui::Shutdown();
	
//	delete debug_window;
//	delete open_file;
	
	return EXIT_SUCCESS;
}
