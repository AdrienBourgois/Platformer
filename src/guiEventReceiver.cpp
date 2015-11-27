#include <SDL2/SDL.h>

#include "guiEventReceiver.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiOption.h"
#include "guiID.h"
#include "txtLogger.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiEventReceiver::GuiEventReceiver(GuiManager* gui)
: gui(gui), mouseX(0), mouseY(0)
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
	setMouseCoords();
	checkButtonHover();
	if (ev->type == SDL_MOUSEBUTTONDOWN)
	{
		if (ev->button.button == SDL_BUTTON_LEFT)
		{
			checkButtonClicked();
		}
	}
	else
	{
		resetPressed();
	}
}
auto GuiEventReceiver::checkMouseOnButton() -> GuiRect*
{
	for (std::vector<GuiRect*>::iterator it = this->gui->getRenderedRect().begin(); it !=  this->gui->getRenderedRect().end(); ++it)
	{
		if ((*it)->getVisible())
		{
			if ((*it)->getTexID() != 0)
			{
				float width = (*it)->getWidth();
				float height = (*it)->getHeight();
				maths::Vector2 pos = (*it)->getPos();
				float leftSide = pos.val[0] - (width/2);
				float rightSide = pos.val[0] + (width/2);
				float bottomSide = pos.val[1] - (height/2);
				float upSide = pos.val[1] + (height/2);

				if ((this->mouseX > leftSide && this->mouseX < rightSide) 
					&& (this->mouseY > bottomSide && this->mouseY < upSide))
					return *it;
			}
		}
	}
	return nullptr;
}
auto GuiEventReceiver::checkButtonClicked() -> void
{
	GuiRect* button = checkMouseOnButton();
	if (button)
	{
		button->setIsPressed(true);
		executeButtonAction(button);
	}
}
auto GuiEventReceiver::checkButtonHover() -> void
{
	GuiRect* button = checkMouseOnButton();
	if (button)
		button->setHover(true);
	else
		resetEvents();
}
auto GuiEventReceiver::executeButtonAction(GuiRect* button) -> void
{
	switch (button->getID())
	{
		case GUI_ID_BUTTON_NEW_GAME:
		{
			std::cout << "new game" << std::endl;
			break;
		}
		case GUI_ID_BUTTON_CONTINUE:
		{
			std::cout << "continue" << std::endl;
			break;
		}
		case GUI_ID_BUTTON_OPTIONS:
		{
			new GuiOption(this->gui);
			break;
		}
		case GUI_ID_BUTTON_QUIT:
		{
			std::cout << "quit" << std::endl;
			break;
		}
	}
}
auto GuiEventReceiver::setMouseCoords() -> void
{
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	this->mouseX -= this->gui->getWidthWin()/2;
	this->mouseY -= this->gui->getHeightWin()/2;
	this->mouseY = -this->mouseY;
}
auto GuiEventReceiver::resetEvents() -> void
{
	resetPressed();
	resetHover();
}
auto GuiEventReceiver::resetPressed() -> void
{
	for (std::vector<GuiRect*>::iterator it = this->gui->getRenderedRect().begin(); it != this->gui->getRenderedRect().end(); ++it)
    {
        (*it)->setIsPressed(false);
    }
}
auto GuiEventReceiver::resetHover() -> void
{
	for (std::vector<GuiRect*>::iterator it = this->gui->getRenderedRect().begin(); it != this->gui->getRenderedRect().end(); ++it)
    {
        (*it)->setHover(false);
    }
}

} // end namespace gui

} // end namespace id
