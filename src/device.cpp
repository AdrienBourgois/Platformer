#include <new>
#include <SDL2/SDL_ttf.h>

#include "device.h"
#include "driver.h"
#include "window.h"
#include "sceneManager.h"
#include "txtLogger.h"
#include "imgui_impl.h"
#include "texture.h"
#include "screenshot.h"
#include "guiManager.h"
#include "guiLogger.h"
#include "guiEventReceiver.h"
#include "eventManager.h"
#include "logger.h"
#include "json/jsonReader.h"
#include "levelEditor.h"
#include "json/jsonWriter.h"

#include <iostream>

namespace {

id::TXTLogger* logger = id::TXTLogger::getInstance();

} // end namespace

namespace id {

auto Device::create() -> std::unique_ptr<Device>
{
	auto* dev = new (std::nothrow) Device;
	if (!dev)
	{
		LOG(L_ERROR,"Failed at creating device in Device::create()");
		SDL_assert(dev);
	}
	return std::unique_ptr<Device>(dev);

}

Device::Device()
{

	LOG(L_INFO,"Creating Device...");

	LOG(L_INFO,"Initializing SDL...");
	SDL_Init(SDL_INIT_VIDEO);
	LOG(L_INFO,"SDL has been initialized");

	json::JsonReader jsonReader;
	std::map<std::string, float> resolution = jsonReader.loadScreenResolution("resolutionScreen");

	_window 	= Window::createWindow(resolution["Width"], resolution["Height"]);	
	_driver		= video::Driver::createDriver(_window.get());
	
	id::imgui_impl::Init();

	_sceneManager	= scene::SceneManager::createSceneManager(_driver.get());
	_gui			= gui::GuiManager::createGuiManager(this, _window.get()->getWidth(), _window.get()->getHeight());
	_eventManager	= event::EventManager::createEventManager();

	levelEditor = new (std::nothrow) LevelEditor(this);
	#ifdef _DEBUG
	debugLogger = new (std::nothrow) DebugLogger;
	#endif
	running = true;
	deltaTime = 0;

	LOG(L_INFO,"Device has been created.");
}

Device::~Device()
{
	LOG(L_INFO,"Deleting device...");
	delete levelEditor;
	#ifdef _DEBUG
	delete debugLogger;
	#endif
	_driver.reset(nullptr);
	_window.reset(nullptr);
	delete _sceneManager;
	_sceneManager = nullptr;
	_gui.reset(nullptr);
	_eventManager.reset(nullptr);

	id::imgui_impl::Shutdown();
	Texture::deleteTextures();
	
	LOG(L_INFO,"Quitting SDL...");
	SDL_Quit();
	LOG(L_INFO,"SDL has been quitted");

	LOG(L_INFO,"Device has been deleted.");
}

auto Device::run() -> bool
{
	imgui_impl::NewFrame(this);
	if(levelEditor->getActive())
		levelEditor->DisplayLevelEditor();
	#ifdef _DEBUG
	if(debugLogger->getVisible())
		debugLogger->DisplayLog();
	#endif
	_sceneManager->clearDeletionQueue();
	this->_eventManager->currentEventListener();

	SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
		imgui_impl::ProcessEvent(&ev);
		this->_gui->getGuiEvt()->eventListener(&ev);
        switch (ev.type)
        {
            case SDL_QUIT:
            {
                close();
                break;
            }
			case SDL_KEYDOWN:
			{
				switch(ev.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
					{
						close();
					}
					break;
					case SDL_SCANCODE_F7:
						Screenshot::take(this);
						break;
					#ifdef _DEBUG
					case SDL_SCANCODE_GRAVE:
					{
						debugLogger->setVisible(!debugLogger->getVisible());
						break;	
					}
					#endif
					default:
						break;
				}
			}
			break;
            
			default:
                break;
        }
    }
	return running;
}
auto Device::close() -> void
{
	running = false;
}

} // end namespace id
