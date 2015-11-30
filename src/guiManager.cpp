#include <SDL2/SDL.h>
#include <memory>

#include "txtLogger.h"
#include "guiManager.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::GuiManager(int windowWidth, int windowHeight)
{
	logger->log("Creating GuiManager...", LL_INFO);

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->camOrtho = {
		2.f/windowWidth, 0.f, 0.f, 0.f,
        0.f, 2.f/-windowHeight, 0.f, 0.f,
        0.f, 0.f, -2.f/(100.f - 0.1f), 0.f,
        0.f, 0.f, 0.f, 1.f
	};

	logger->log("GuiManager created", LL_INFO);
}
GuiManager::~GuiManager()
{
	logger->log("Deleting GuiManager...", LL_INFO);

	logger->log("GuiManager deleted", LL_INFO);
}
auto GuiManager::createGuiManager(int windowWidth, int windowHeight) -> std::unique_ptr<GuiManager>
{
	GuiManager* gui = new (std::nothrow) GuiManager(windowWidth, windowHeight);
	if (!gui)
	{
		logger->log("Failed at creating gui in GuiManager::createGuiManager()", LL_ERROR);
		SDL_assert(gui);
	}
	return std::unique_ptr<GuiManager>(gui);
}

} // end namespace gui

} // end namespace id
