#include "txtLogger.h"
#include "guiLifeBar.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiID.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiLifeBar::GuiLifeBar(GuiManager* gui, float max)
: gui(gui), max(max), current(max)
{
	logger->log("Creating GuiLifeBar...", LL_INFO);

	this->id = GUI_ID_RECT_LIFE_BAR;
	gui->addRect(nullptr, gui->getWidth()/2.2 - max/2, gui->getHeight()/2.2, max, 20, this->id, true, {0.f, 0.7f, 0.f, 1.f});
	gui->getElementFromID(this->id)->addGradient({0.f, 1.f, 0.f, 1.f}, {1.f, 0.f, 0.f, 1.f});

	logger->log("GuiLifeBar created", LL_INFO);
}
GuiLifeBar::~GuiLifeBar()
{
	logger->log("Deleting GuiLifeBar...", LL_INFO);

	this->gui = nullptr;

	logger->log("GuiLifeBar deleted", LL_INFO);
}
auto GuiLifeBar::refreshLifeBar(float damage) -> void
{
	this->current -= damage;

	if (current < 0)
		current = 0;

	float percent = (current*100.f)/max;
	float green = percent/100.f;
	float red = 1.f - (percent/100.f);

	this->gui->getElementFromID(this->id)->addGradient({red, green, 0.f, 1.f}, {1.f, 0.f, 0.f, 1.f});
	this->gui->getElementFromID(this->id)->refreshRect(this->gui->getWidth()/2.2 - current/2, this->gui->getHeight()/2.2, current, 20);
}

} // end namespace gui

} // end namespace id
