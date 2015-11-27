#ifndef GUI_OPTION_H_INCLUDED
#define GUI_OPTION_H_INCLUDED

namespace id {
namespace gui {

class GuiManager;

class GuiOption
{
public:
	GuiOption(GuiManager* gui);
	~GuiOption();

private:
	GuiManager* gui;
};

} // end namespace gui

} // end namespace id


#endif // GUI_OPTION_H_INCLUDED

