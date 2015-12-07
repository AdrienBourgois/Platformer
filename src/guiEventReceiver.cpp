#include <SDL2/SDL.h>
#include <functional>
#include <string>

#include "txtLogger.h"
#include "guiEventReceiver.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiButton.h"
#include "json/jsonWriter.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiEventReceiver::GuiEventReceiver(GuiManager* gui)
: gui(gui), mouseX(0), mouseY(0), listenKeys(false)
{
	logger->log("Creating GuiEventReceiver...", LL_INFO);

	logger->log("GuiEventReceiver created", LL_INFO);
}
GuiEventReceiver::~GuiEventReceiver()
{
	logger->log("Deleting GuiEventReceiver...", LL_INFO);

	this->gui = nullptr;

	logger->log("GuiEventReceiver deleted", LL_INFO);
}
auto GuiEventReceiver::eventListener(SDL_Event* ev) -> void
{
	refreshMouseCoords();
	listenNextKey(ev);
	
	if (ev->type == SDL_MOUSEBUTTONDOWN)
	{
		if (ev->button.button == SDL_BUTTON_LEFT)
		{
			checkMouseOnButton();
		}
	}
}
auto GuiEventReceiver::checkMouseOnButton() -> void
{
	resetEvents();
	std::vector<GuiRect*> drawRect = this->gui->getDrawRect();
	for (auto it = drawRect.begin(); it !=  drawRect.end(); ++it)
	{
		if ((*it)->getVisible() && (*it)->getListenEvent())
		{
			float posX = (*it)->getPosX();
			float posY = (*it)->getPosY();
			float width = (*it)->getWidth();
			float height = (*it)->getHeight();
			float leftSide = posX - (width/2);
			float rightSide = posX + (width/2);
			float upSide = posY - (height/2);
			float downSide = posY + (height/2);
			if ((this->mouseX > leftSide && this->mouseX < rightSide)
				&& (this->mouseY > upSide && this->mouseY < downSide))
			{
				(*it)->setIsPressed(true);
				std::function<void()> func = (*it)->getFunc();
				if (func)
					func();
				else
					logger->log("Listen event on a button without function", LL_WARNING);

				return;
			}
		}
	}
}
auto GuiEventReceiver::listenNextKey(SDL_Event* ev) -> void
{
	if (ev->type == SDL_KEYDOWN && this->listenKeys)
	{
		std::string key = SDL_GetScancodeName(ev->key.keysym.scancode);
		if (key != "")
		{
			GuiButton* but = static_cast<GuiButton*>(this->gui->getPressedElement());
			but->setNewText(key);
			this->listenKeys = false;
			resetEvents();
		}
	}
}
auto GuiEventReceiver::refreshMouseCoords() -> void
{
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	this->mouseX -= this->gui->getWidth()/2;
	this->mouseY -= this->gui->getHeight()/2;
	this->mouseY = -this->mouseY;
}
auto GuiEventReceiver::resetEvents() -> void
{
	this->listenKeys = false;
	std::vector<GuiRect*> drawRect = this->gui->getDrawRect();
    for (auto it = drawRect.begin(); it !=  drawRect.end(); ++it)
		(*it)->setIsPressed(false);
}

} // end namespace gui

} // end namespace id
