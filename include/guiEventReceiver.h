#ifndef GUI_EVENT_RECEIVER_H_INCLUDED
#define GUI_EVENT_RECEIVER_H_INCLUDED

#include <SDL2/SDL.h>

#include "guiManager.h"

namespace id {
namespace gui {

class GuiEventReceiver
{
public:
	GuiEventReceiver(GuiManager* gui);
	~GuiEventReceiver();

	auto eventListener(SDL_Event* ev) -> void;
	auto checkMouseOnButton() -> void;

	auto getMouseCoords() -> void;

private:
	GuiManager* gui;
	int mouseX, mouseY;
};

} // end namespace 

} // end namespace id

#endif // GUI_EVENT_RECEIVER_H_INCLUDED
