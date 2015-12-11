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
#include "guiEventReceiver.h"
#include "eventManager.h"
#include "logger.h"
#include "json/jsonReader.h"

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
		logger->log("Failed at creating device in Device::create()", LL_ERROR);
		SDL_assert(dev);
	}
	LOG(L_ERROR,"BONJOUR", "i54");
	return std::unique_ptr<Device>(dev);

}

Device::Device()
{
	logger->log("Creating Device...", LL_DEBUG);

	logger->log("Initializing SDL...", LL_DEBUG);
	SDL_Init(SDL_INIT_VIDEO);
	logger->log("SDL has been initialized");

	json::JsonReader jsonReader;
	std::map<std::string, float> resolution = jsonReader.loadScreenResolution("resolutionScreen");

	_window		 	= Window::createWindow(resolution["Width"], resolution["Height"]);	
	_driver			= video::Driver::createDriver(_window.get());
	
	id::imgui_impl::Init();

	_sceneManager	= scene::SceneManager::createSceneManager(_driver.get());
	_gui			= gui::GuiManager::createGuiManager(this, _window.get()->getWidth(), _window.get()->getHeight());
	_eventManager	= event::EventManager::createEventManager();

	running = true;
	deltaTime = 0;

	logger->log("Device has been created.");
}

Device::~Device()
{
	logger->log("Deleting device...", LL_DEBUG);

	_driver.reset(nullptr);
	_window.reset(nullptr);
	delete _sceneManager;
	_sceneManager = nullptr;
	_gui.reset(nullptr);
	_eventManager.reset(nullptr);

	id::imgui_impl::Shutdown();
	Texture::deleteTextures();
	
	logger->log("Quitting SDL...", LL_DEBUG);
	SDL_Quit();
	logger->log("SDL has been quitted");

	logger->log("Device has been deleted.");
}

auto Device::run() -> bool
{
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
