#include <typeinfo>
#include <new>
#include <stdio.h>
#include "device.h"
#include "window.h"
#include "txtLogger.h"
#include "meshSceneNode.h"
#include "cameraSceneNode.h"
#include "guiTtf.h"
#include "imgui.h"
#include "imgui_impl.h"
#include "guiDebugWindow.h"
#include "guiOpenFile.h"
#include "driver.h"
#include "fileUtility.h"
#include "SDL2/SDL_ttf.h"
#include <map>
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

	std::cout << "Bonjour" << std::endl;	
	TTF_Init();
	if(TTF_Init() == -1){
		fprintf(stderr, "Error Init TTF: %s\n", TTF_GetError());
	}

	id::GuiTtf* GTtf = new (std::nothrow) id::GuiTtf();
	GTtf->addFont("ProggyClean.ttf");
	GTtf->pickColor();
	GTtf->createText("Bonjour teste");

/*

	TTF_Font *font = nullptr;
	font = TTF_OpenFont("./assets/extra_fonts/ProggyClean.ttf", 65);
	if(!font){
	std::cout<< "pb font" << std::endl;
	}
	
	SDL_Color colorb = {0,0,0,255};

	SDL_Surface* text = TTF_RenderText_Blended(font, "Bonjour test", colorb);
	(void)text;
*/
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
	TTF_CloseFont(GTtf->getMapFonts().find("ProggyClean.ttf")->second);
	ImGui::Shutdown();
	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
