#ifndef GUI_LIFE_BAR_INCLUDED
#define GUI_LIFE_BAR_INCLUDED

#include "guiManager.h"
#include "guiRect.h"

namespace id {
namespace gui {

class GuiLifeBar
{
public:
	GuiLifeBar(GuiManager* gui, float max);
	~GuiLifeBar();

	auto refreshLifeBar(float damage) -> void;

private:
	GuiManager* gui;
	int id;
	float max;
	float current;
};

} // end namespace gui

} // end namespace id

#endif // GUI_LIFE_BAR_INCLUDED

