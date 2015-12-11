#ifndef GUI_LIFE_BAR_INCLUDED
#define GUI_LIFE_BAR_INCLUDED


namespace id {
namespace gui {

class GuiManager;
class GuiRect;

class GuiLifeBar
{
public:
	GuiLifeBar(GuiManager* gui, float max);
	~GuiLifeBar();
	GuiLifeBar(GuiLifeBar const&) = delete;
	GuiLifeBar(GuiLifeBar&&) = delete;
	auto operator=(GuiLifeBar const&) -> GuiLifeBar& = delete;
	auto operator=(GuiLifeBar&&) -> GuiLifeBar& = delete;

	auto refreshLifeBar(float damage) -> void;

private:
	GuiManager* gui;
	int 		id;
	float 		max;
	float 		current;
};

} // namespace gui

} // namespace id

#endif // GUI_LIFE_BAR_INCLUDED

