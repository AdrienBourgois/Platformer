#include <functional>
#include <vector>

#include "txtLogger.h"
#include "guiMenu.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiButton.h"
#include "guiID.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiMenu::GuiMenu(GuiManager* gui)
: gui(gui)
{
	logger->log("Creating GuiMenu...", LL_INFO);

	logger->log("GuiMenu created", LL_INFO);
}
GuiMenu::~GuiMenu()
{
	logger->log("Deleting GuiMenu...", LL_INFO);

	logger->log("GuiMenu deleted", LL_INFO);
}
auto GuiMenu::createMenuTitleScreen() -> void
{
	this->gui->addRect(nullptr, 0, 0, 300, 350, GUI_ID_RECT_MENU, true, {0.f, 0.f, 0.f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_MENU);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU), 0, 120, 100, 50, GUI_ID_BUTTON_NEW_GAME, true, {0.5f, 0.f, 0.f, 1.f}, "New Game", {1.f, 1.f, 1.f, 1.f}, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_NEW_GAME);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU), 0, 40, 100, 50, GUI_ID_BUTTON_LOAD, true, {0.5, 0.f, 0.f, 1.f}, "Load", {1.f, 1.f, 1.f, 1.f}, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_LOAD);

	GuiManager* gui = this->gui;
	std::function<void()> func = [gui]() { gui->addButton(nullptr, 200, 0, 200, 50, 10, true, {0.5f, 0.f, 0.f, 1.f}, "test std::function", {1.f, 1.f, 1.f, 1.f}, nullptr); };

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU), 0, -40, 100, 50, GUI_ID_BUTTON_SETTINGS, true, {0.5f, 0.f, 0.f, 1.f}, "Settings", {1.f, 1.f, 1.f, 1.f}, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_SETTINGS);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU), 0, -120, 100, 50, GUI_ID_BUTTON_QUIT, true, {0.5f, 0.f, 0.f, 1.f}, "Quit", {1.f, 1.f, 1.f, 1.f}, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_QUIT);
}
auto GuiMenu::createMenuSettings() -> void
{
	
}
auto GuiMenu::setVisible(bool visible) -> void
{
	(void)visible;
}

} // end namespace gui

} // end namespace id
