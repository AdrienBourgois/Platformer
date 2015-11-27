#ifndef GUI_MENU_H_INCLUDED
#define GUI_MENU_H_INCLUDED

#include <vector>

namespace id {
namespace gui {

class GuiManager;
class GuiRect;

class GuiMenu
{
public:
	GuiMenu(GuiManager* gui);
	~GuiMenu();

	auto createMenuTitleScreen() -> void;
	auto deleteMenu() -> void;

	auto setVisible(bool visible) -> void;

private:
	GuiManager* gui;
	std::vector<int> rectMenu;
};

} // end namespace gui

} // end namespace id

#endif // GUI_MENU_H_INCLUDED

