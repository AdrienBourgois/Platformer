#include "txtLogger.h"
#include "guiLifeBar.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiID.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiLifeBar::GuiLifeBar(GuiManager* gui, float max)
: gui(gui), max(max)
{
	logger->log("Creating GuiLifeBar...", LL_INFO);

	this->id = GUI_ID_RECT_LIFE_BAR;
	gui->addRect(nullptr, gui->getWidth()/2.2 - max/2, gui->getHeight()/2.2, max, 20, this->id, true, {0.f, 0.7f, 0.f, 1.f});
	gui->getElementFromID(this->id)->addGradient({0.f, 0.7f, 0.f, 1.f}, {0.7, 0.f, 0.f, 1.f});

	logger->log("GuiLifeBar created", LL_INFO);
}
GuiLifeBar::~GuiLifeBar()
{
	logger->log("Deleting GuiLifeBar...", LL_INFO);

	this->gui = nullptr;

	logger->log("GuiLifeBar deleted", LL_INFO);
}

} // end namespace gui

} // end namespace id
