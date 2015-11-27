#include "guiOption.h"
#include "guiManager.h"
#include "txtLogger.h"
#include "guiID.h"

namespace {
    id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiOption::GuiOption(GuiManager* gui)
: gui(gui)
{
	logger->log("Creating GuiOption...", LL_INFO);

	gui->addRect(nullptr, {0,0}, 400, 600, {0.f, 0.f, 1.f, 1.f}, true, GUI_ID_RECT_OPTION);
	gui->addButton(gui->getRectFromID(GUI_ID_RECT_OPTION), {-50,0}, 100, 30, {0.f, 0.f, 0.f, 0.f}, {0.f, 0.f, 0.f, 1.f}, "Move Forward", true, GUI_ID_BUTTON_MOVE_FORWARD_TEXT);
	gui->addButton(gui->getRectFromID(GUI_ID_RECT_OPTION), {30, 0}, 30, 30, {0.3f, 0.3f, 0.3f, 1.f}, {0.f, 0.f, 0.f, 1.f}, "W", true, GUI_ID_BUTTON_MOVE_FORWARD_KEY);

	logger->log("GuiOption created", LL_INFO);
}
GuiOption::~GuiOption()
{
	logger->log("Deleting GuiOption...", LL_INFO);	

	this->gui = nullptr;

	logger->log("GuiOption deleted", LL_INFO);
}


} // end namespace gui

} // end namespace id
