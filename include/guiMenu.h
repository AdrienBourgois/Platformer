#ifndef GUI_MENU_H_INCLUDED
#define GUI_MENU_H_INCLUDED

#include <vector>

#include "guiManager.h"

namespace id {
namespace gui {

class GuiMenu
{
public:
	GuiMenu(GuiManager* gui);
	~GuiMenu();

	auto createMenuTitleScreen() -> void;
	auto createMenuSettings() -> void;
	auto deleteMenu() -> void;

	auto setVisible(bool visible) -> void;

private:
	GuiManager* gui;
	std::vector<int> idRectMenu;
	int windowWidth, windowHeight;
};

} // end namespace gui

} // end namespace id

#endif // GUI_MENU_H_INCLUDED
