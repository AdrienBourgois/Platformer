#include <SDL2/SDL.h>
#include <functional>
#include <string>

#include "txtLogger.h"
#include "guiEventReceiver.h"
#include "guiManager.h"
#include "guiRect.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiEventReceiver::GuiEventReceiver(GuiManager* gui)
: gui(gui)
{
	logger->log("Creating GuiEventReceiver...", LL_INFO);

	logger->log("GuiEventReceiver created", LL_INFO);
}
GuiEventReceiver::~GuiEventReceiver()
{
	logger->log("Deleting GuiEventReceiver...", LL_INFO);

	logger->log("GuiEventReceiver deleted", LL_INFO);
}
auto GuiEventReceiver::eventListener(SDL_Event* ev) -> void
{
	getMouseCoords();
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
				(*it)->setPressed(true);
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
auto GuiEventReceiver::getMouseCoords() -> void
{
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	this->mouseX -= this->gui->getWidth()/2;
	this->mouseY -= this->gui->getHeight()/2;
	this->mouseY = -this->mouseY;
}

} // end namespace gui

} // end namespace id
