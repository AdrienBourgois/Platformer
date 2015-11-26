#ifndef GUI_MENU_H_INCLUDED
#define GUI_MENU_H_INCLUDED

#include <vector>

namespace id {
namespace gui {

class GuiManager:
class GuiRect;

class GuiMenu
{
public:
	~GuiMenu();

	auto createMenuTitleScreen() -> void;
	auto deleteMenuTitleScreen() -> void;

private:
	GuiMenu();

	std::vector<GuiRect*> rectMenu;
};

} // end namespace gui

} // end namespace id

#endif // GUI_MENU_H_INCLUDED

