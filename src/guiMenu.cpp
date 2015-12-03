#include <functional>
#include <vector>

#include "txtLogger.h"
#include "guiMenu.h"
#include "guiManager.h"
#include "guiEventReceiver.h"
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

	this->windowWidth = gui->getWidth();
	this->windowHeight = gui->getHeight();

	logger->log("GuiMenu created", LL_INFO);
}
GuiMenu::~GuiMenu()
{
	logger->log("Deleting GuiMenu...", LL_INFO);

	logger->log("GuiMenu deleted", LL_INFO);
}
auto GuiMenu::createMenuTitleScreen() -> void
{
	maths::Vector4 colorBut = {0.5f, 0.f, 0.f, 1.f};
	maths::Vector4 colorText = {1.f, 1.f, 1.f, 1.f};

	this->gui->addRect(nullptr, 0, 0, this->windowWidth/4, this->windowHeight/2, GUI_ID_RECT_MENU_TITLE, true, {0.f, 0.f, 0.f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_MENU_TITLE);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, this->windowHeight/6, this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_NEW_GAME, true, colorBut, "New Game", colorText, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_NEW_GAME);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, this->windowHeight/18, this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_LOAD, true, colorBut, "Load", colorText, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_LOAD);

	GuiManager* gui = this->gui;
	std::function<void()> func = [gui, this]() { this->setVisible(false); gui->addMenuSettings(); };

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, -(this->windowHeight/18), this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_SETTINGS, true, colorBut, "Settings", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_SETTINGS);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, -(this->windowHeight/6), this->windowWidth/8, this->windowHeight/13, GUI_ID_BUTTON_QUIT, true, colorBut, "Quit", colorText, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_QUIT);
}
auto GuiMenu::createMenuSettings() -> void
{
	maths::Vector4 colorBut = {0.5f, 0.f, 0.f, 1.f};
	maths::Vector4 colorText = {1.f, 1.f, 1.f, 1.f};

	GuiManager* gui = this->gui;
	std::function<void()> func = [gui]() { gui->getGuiEvt()->setListenKeys(true); };

	this->gui->addRect(nullptr, 0, 0, this->windowWidth/1.2, this->windowHeight/1.2, GUI_ID_RECT_MENU_SETTINGS, true, {0.f, 0.f, 0.f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_MENU_SETTINGS);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), this->windowHeight/3.6, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_FORWARD, true, "Forward", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_FORWARD);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), this->windowHeight/3.6, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_FORWARD, true, colorBut, "W", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_FORWARD);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), this->windowHeight/7, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_BACKWARD, true, "Backward", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_BACKWARD);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), this->windowHeight/7, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_BACKWARD, true, colorBut, "S", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_BACKWARD);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), 0, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_TURN_RIGHT, true, "Turn Right", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_RIGHT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), 0, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_TURN_RIGHT, true, colorBut, "D", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_TURN_RIGHT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), -(this->windowHeight/7), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_TURN_LEFT, true, "Turn Left", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_LEFT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), -(this->windowHeight/7), this->windowWidth/32, this->windowHeight/18, GUI_ID_TEXT_TURN_LEFT, true, colorBut, "A", colorText, func);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_LEFT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), -(this->windowHeight/3.6), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_STRAFE_RIGHT, true, "Strafe Right", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_STRAFE_RIGHT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), -(this->windowHeight/3.6), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_STRAFE_RIGHT, true, colorBut, "E", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_STRAFE_RIGHT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), this->windowHeight/3.6, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_STRAFE_LEFT, true, "Strafe Left", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_STRAFE_LEFT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), this->windowHeight/3.6, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_STRAFE_LEFT, true, colorBut, "Q", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_STRAFE_LEFT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), this->windowHeight/7, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_RUN, true, "Run", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_RUN);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), this->windowHeight/7, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_RUN, true, colorBut, "R", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RUN);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), 0, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_JUMP, true, "Jump", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_JUMP);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), 0, this->windowWidth/24, this->windowHeight/18, GUI_ID_BUTTON_JUMP, true, colorBut, "Space", colorText, nullptr);
	this->idRectMenu.push_back(GUI_ID_BUTTON_JUMP);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), -(this->windowHeight/7), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_SHOOT, true, "Shoot", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_SHOOT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), -(this->windowHeight/7), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_SHOOT, true, colorBut, "J", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_SHOOT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), -(this->windowHeight/3.6), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_PAUSE, true, "Pause", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_PAUSE);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), -(this->windowHeight/3.6), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_PAUSE, true, colorBut, "P", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_PAUSE);
}
auto GuiMenu::setVisible(bool visible) -> void
{
	this->gui->getElementFromID(this->idRectMenu.front())->setVisible(visible);
}

} // end namespace gui

} // end namespace id
