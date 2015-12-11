#include <functional>
#include <vector>

#include "device.h"
#include "txtLogger.h"
#include "guiMenu.h"
#include "guiManager.h"
#include "guiEventReceiver.h"
#include "guiRect.h"
#include "guiButton.h"
#include "guiID.h"
#include "json/jsonReader.h"
#include "eventManager.h"
#include "eventPlayer.h"
#include "levelEditor.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiMenu::GuiMenu(GuiManager* gui)
: gui(gui), id(-1)
{
	logger->log("Creating GuiMenu...", LL_INFO);

	this->windowWidth = gui->getWidth();
	this->windowHeight = gui->getHeight();

	logger->log("GuiMenu created", LL_INFO);
}
GuiMenu::~GuiMenu()
{
	logger->log("Deleting GuiMenu...", LL_INFO);

	this->gui = nullptr;
	this->idRectMenu.clear();

	logger->log("GuiMenu deleted", LL_INFO);
}
auto GuiMenu::createMenuTitleScreen(std::function<void()> funcQuit) -> void
{
	this->id = GUI_ID_MENU_TITLE_SCREEN;

	maths::Vector4 colorBut = {0.5f, 0.f, 0.f, 1.f};
	maths::Vector4 colorText = {1.f, 1.f, 1.f, 1.f};

	this->gui->addRect(nullptr, 0, 0, this->windowWidth/4, this->windowHeight/1.4, GUI_ID_RECT_MENU_TITLE, true, {0.f, 0.f, 0.f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_MENU_TITLE);

	json::JsonReader* jsonReader = new json::JsonReader();
	GuiManager* gui = this->gui;
	std::function<void()> funcNewGame = [jsonReader, gui, this]() {jsonReader->loadAllNode(gui->getDevice(), "level1"); this->deleteMenu();};

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, this->windowHeight/4.2, this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_NEW_GAME, true, colorBut, "New Game", colorText, funcNewGame);
	this->idRectMenu.push_back(GUI_ID_BUTTON_NEW_GAME);

	std::function<void()> funcLoad = [jsonReader, gui, this]() {jsonReader->loadAllNode(gui->getDevice(), "partie1"); this->deleteMenu();};

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, this->windowHeight/8, this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_LOAD, true, colorBut, "Load", colorText, funcLoad);
	this->idRectMenu.push_back(GUI_ID_BUTTON_LOAD);

	std::function<void()> funcLevelEditor = [gui, this]() {gui->getDevice()->getLevelEditor()->setActive(true); this->deleteMenu();};
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, 0, this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_LEVEL_EDITOR, true, colorBut, "Level Editor", colorText, funcLevelEditor);
	this->idRectMenu.push_back(GUI_ID_BUTTON_LEVEL_EDITOR);

	std::function<void()> func = [gui, this]() { this->setVisible(false); gui->addMenuSettings(); };

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, -(this->windowHeight/8), this->windowWidth/8, this->windowHeight/12, GUI_ID_BUTTON_SETTINGS, true, colorBut, "Settings", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_SETTINGS);

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_TITLE), 0, -(this->windowHeight/4.2), this->windowWidth/8, this->windowHeight/13, GUI_ID_BUTTON_QUIT, true, colorBut, "Quit", colorText, funcQuit);
	this->idRectMenu.push_back(GUI_ID_BUTTON_QUIT);
}
auto GuiMenu::createMenuSettings() -> void
{
	this->id = GUI_ID_MENU_SETTINGS;

	maths::Vector4 colorBut = {0.5f, 0.f, 0.f, 1.f};
	maths::Vector4 colorText = {1.f, 1.f, 1.f, 1.f};

	GuiManager* gui = this->gui;
	std::function<void()> func = [gui]() { gui->getGuiEvt()->setListenKeys(true); };

	json::JsonReader jsonReader;
	std::map<std::string, std::string> values = jsonReader.loadKeyBinding();

	this->gui->addRect(nullptr, 0, 0, this->windowWidth/1.2, this->windowHeight/1.2, GUI_ID_RECT_MENU_SETTINGS, true, {0.f, 0.f, 0.f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_MENU_SETTINGS);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), this->windowHeight/3.6, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_FORWARD, true, "Forward", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_FORWARD);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), this->windowHeight/3.6, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_FORWARD, true, colorBut, values["Forward"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_FORWARD);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), this->windowHeight/7, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_BACKWARD, true, "Backward", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_BACKWARD);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), this->windowHeight/7, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_BACKWARD, true, colorBut, values["Backward"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_BACKWARD);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), 0, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_TURN_RIGHT, true, "Turn Right", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_RIGHT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), 0, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_TURN_RIGHT, true, colorBut, values["Turn_right"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_TURN_RIGHT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), -(this->windowHeight/7), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_TURN_LEFT, true, "Turn Left", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_LEFT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), -(this->windowHeight/7), this->windowWidth/32, this->windowHeight/18, GUI_ID_TEXT_TURN_LEFT, true, colorBut, values["Turn_left"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_TEXT_TURN_LEFT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/3.2), -(this->windowHeight/3.6), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_STRAFE_RIGHT, true, "Strafe Right", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_STRAFE_RIGHT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/4.2), -(this->windowHeight/3.6), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_STRAFE_RIGHT, true, colorBut, values["Strafe_right"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_STRAFE_RIGHT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), this->windowHeight/3.6, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_STRAFE_LEFT, true, "Strafe Left", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_STRAFE_LEFT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), this->windowHeight/3.6, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_STRAFE_LEFT, true, colorBut, values["Strafe_left"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_STRAFE_LEFT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), this->windowHeight/7, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_RUN, true, "Run", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_RUN);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), this->windowHeight/7, this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_RUN, true, colorBut, values["Run"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RUN);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), 0, this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_JUMP, true, "Jump", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_JUMP);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), 0, this->windowWidth/24, this->windowHeight/18, GUI_ID_BUTTON_JUMP, true, colorBut, values["Jump"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_JUMP);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), -(this->windowHeight/7), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_SHOOT, true, "Quick Save", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_SHOOT);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), -(this->windowHeight/7), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_SHOOT, true, colorBut, values["Quick_save"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_SHOOT);
	this->gui->addStaticText(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/8.4), -(this->windowHeight/3.6), this->windowWidth/16, this->windowHeight/18, GUI_ID_TEXT_PAUSE, true, "Pause", colorText);
	this->idRectMenu.push_back(GUI_ID_TEXT_PAUSE);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), -(this->windowWidth/22), -(this->windowHeight/3.6), this->windowWidth/32, this->windowHeight/18, GUI_ID_BUTTON_PAUSE, true, colorBut, values["Pause"], colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_PAUSE);

	std::function<void()> funcResolution = [gui]() {gui->addMenuResolution(); gui->getGuiEvt()->resetEvents();};
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), this->windowWidth/7, this->windowHeight/3.6, this->windowWidth/16, this->windowHeight/16, GUI_ID_BUTTON_RESOLUTION, true, colorBut, "Resolution", colorText, funcResolution);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RESOLUTION);

	std::function<void()> funcButAccept = [this, gui]() {
		static_cast<event::EventPlayer*>(gui->getDevice()->getEventManager()->getEventFromName("EventPlayer"))->loadKeys();
		if(gui->getMenuFromID(GUI_ID_MENU_RESOLUTION)){
			gui->getMenuFromID(GUI_ID_MENU_RESOLUTION)->deleteMenu();
		} 
		this->deleteMenu();
		gui->getListMenus().front()->setVisible(true);
	};
		this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_MENU_SETTINGS), this->windowWidth/3, -(this->windowHeight/2.8), this->windowWidth/15, this->windowHeight/16, GUI_ID_BUTTON_BACK, true, colorBut, "Accept", colorText, funcButAccept);
	this->idRectMenu.push_back(GUI_ID_BUTTON_BACK);
}
auto GuiMenu::createMenuResolution() -> void
{
	this->id = GUI_ID_MENU_RESOLUTION;

	maths::Vector4 colorBut = {0.5f, 0.f, 0.f, 1.f};
	maths::Vector4 colorText = {1.f, 1.f, 1.f, 1.f};

	GuiRect* parent = this->gui->getElementFromID(GUI_ID_BUTTON_RESOLUTION);
	this->gui->addRect(parent, 0, -this->windowHeight/7.2 - parent->getHeight()/2, this->windowWidth/5, this->windowHeight/3.6, GUI_ID_RECT_RESOLUTION, true, {0.2f, 0.2f, 0.2f, 1.f});
	this->idRectMenu.push_back(GUI_ID_RECT_RESOLUTION);

	GuiManager* gui = this->gui;
	std::function<void()> func = [gui]() {gui->getGuiEvt()->changeResolution();};

	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_RESOLUTION), 0, this->windowHeight/12, this->windowWidth/7.8, this->windowHeight/24, GUI_ID_BUTTON_RESOLUTION_640X480, true, colorBut, "640x480", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RESOLUTION_640X480);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_RESOLUTION), 0, 0, this->windowWidth/7.8, this->windowHeight/24, GUI_ID_BUTTON_RESOLUTION_1280X720, true, colorBut, "1280x720", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RESOLUTION_1280X720);
	this->gui->addButton(this->gui->getElementFromID(GUI_ID_RECT_RESOLUTION), 0, -this->windowHeight/12, this->windowWidth/7.8, this->windowHeight/24, GUI_ID_BUTTON_RESOLUTION_1920X1080, true, colorBut, "1480x860", colorText, func);
	this->idRectMenu.push_back(GUI_ID_BUTTON_RESOLUTION_1920X1080);
}
auto GuiMenu::deleteMenu() -> void
{
	for (auto it = this->idRectMenu.begin(); it != this->idRectMenu.end(); ++it)
	{
		delete this->gui->getElementFromID(*it);
		this->gui->removeToRender(this->gui->getElementFromID(*it));
	}
	this->gui->removeMenu(this);
	delete this;
}
auto GuiMenu::setVisible(bool visible) -> void
{
	this->gui->getElementFromID(this->idRectMenu.front())->setVisible(visible);
}

} // end namespace gui

} // end namespace id
