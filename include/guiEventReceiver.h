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

	auto eventListener(SDL_Event* ev) -> bool;
	auto checkButtonClicked() -> bool;
	auto setMouseCoords() -> void;

private:
	GuiManager* gui;

	int mouseX;
	int mouseY;
};

} // end namespace gui

} // end namespace id

#endif
