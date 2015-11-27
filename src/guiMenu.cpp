#include <vector>

#include "txtLogger.h"
#include "guiManager.h"
#include "guiMenu.h"
#include "guiRect.h"
#include "guiID.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiMenu::GuiMenu(GuiManager* gui)
: gui(gui)
{
	logger->log("Creating Menu...", LL_INFO);

	logger->log("Menu created", LL_INFO);
}
GuiMenu::~GuiMenu()
{
	logger->log("Deleting GuiMenu...", LL_INFO);

	this->gui = nullptr;
	this->rectMenu.clear();

	logger->log("GuiMenu deleted", LL_INFO);
}
auto GuiMenu::createMenuTitleScreen() -> void
{
	this->gui->addRect(nullptr, {0, 0}, 300, 350, {0.f, 0.f, 1.f, 1.f}, true, GUI_ID_RECT_MENU);
	this->rectMenu.push_back(GUI_ID_RECT_MENU);
	this->gui->addButton(this->gui->getRectFromID(GUI_ID_RECT_MENU), {0, 120}, 100, 50, {0.3f, 0.3f, 0.3f, 1.f}, {0.f, 0.f, 0.f, 1.f}, "New Game", true, GUI_ID_BUTTON_NEW_GAME);
	this->rectMenu.push_back(GUI_ID_BUTTON_NEW_GAME);
	this->gui->addButton(this->gui->getRectFromID(GUI_ID_RECT_MENU), {0, 40}, 100, 50, {0.3f, 0.3f, 0.3f, 1.f}, {0.f, 0.f, 0.f, 1.f}, "Continue", true, GUI_ID_BUTTON_CONTINUE);
	this->rectMenu.push_back(GUI_ID_BUTTON_CONTINUE);
	this->gui->addButton(this->gui->getRectFromID(GUI_ID_RECT_MENU), {0, -40}, 100, 50, {0.3f, 0.3f, 0.3f, 1.f}, {0.f, 0.f, 0.f, 1.f}, "Options", true, GUI_ID_BUTTON_OPTIONS);
	this->rectMenu.push_back(GUI_ID_BUTTON_OPTIONS);
	this->gui->addButton(this->gui->getRectFromID(GUI_ID_RECT_MENU), {0, -120}, 100, 50, {0.3f, 0.3f, 0.3f, 1.f}, {0.f, 0.f, 0.f, 1.f}, "Quit", true, GUI_ID_BUTTON_QUIT);
	this->rectMenu.push_back(GUI_ID_BUTTON_QUIT);
}
auto GuiMenu::deleteMenu() -> void
{
	for (std::vector<int>::iterator it = this->rectMenu.begin(); it != this->rectMenu.end(); ++it)
	{
		delete this->gui->getRectFromID(*it);
		this->gui->removeToRender(this->gui->getRectFromID(*it));
	}
	delete this;
}
auto GuiMenu::setVisible(bool visible) -> void
{
	this->gui->getRectFromID(this->rectMenu.front())->setVisible(visible);
}

} // end namespace gui

} // end namespace id
