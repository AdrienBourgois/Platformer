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

	LOG(L_ERROR, 32, 454,4554754,455454);
	std::unique_ptr<id::Device> device = device->create();
	
	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;
	}

	id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
    (void)cam;

	
	id::DebugLogger* debug_logger = new (std::nothrow) id::DebugLogger;	
	id::DebugWindow* debug_window = new (std::nothrow) id::DebugWindow();
	id::OpenFile* open_file = new (std::nothrow) id::OpenFile();

//	bool visible2 = true;	
	while (device->run())
	{
		device->getDriver()->clear();
		device->getSceneManager()->draw();
		id::imgui_impl::NewFrame(device.get());
		
//		ImGui::ShowTestWindow(&visible2);
		debug_window->Display(device.get());
		open_file->Display(device.get());
		
		debug_logger->DisplayLog();	
		#ifdef _DEBUG
			ImGui::Render();
		#endif
		device->getWindow()->swap();
	}

	ImGui::Shutdown();
	delete debug_logger;	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
