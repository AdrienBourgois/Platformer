#ifndef GUI_MENU_H_INCLUDED
#define GUI_MENU_H_INCLUDED

#include <functional>
#include <vector>

namespace id {
namespace gui {

class GuiManager;

class GuiMenu
{
public:
	GuiMenu(GuiManager* gui);
	~GuiMenu();
	GuiMenu(GuiMenu const&) = delete;
	GuiMenu(GuiMenu&&) = delete;
	auto operator=(GuiMenu const&) -> GuiMenu& = delete;
	auto operator=(GuiMenu&&) -> GuiMenu& = delete;


	auto createMenuTitleScreen(std::function<void()> funcQuit) -> void;
	auto createMenuSettings() -> void;
	auto createMenuResolution() -> void;
	auto deleteMenu() -> void;

	auto getID() const -> int { return this->id; }

	auto setVisible(bool visible) -> void;

private:
	GuiManager* gui;
	int id;
	std::vector<int> idRectMenu;
	int windowWidth, windowHeight;
};

} // namespace gui
} // namespace id

#endif // GUI_MENU_H_INCLUDED
