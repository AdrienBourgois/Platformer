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
	auto checkMouseOnButton() -> GuiRect*;
	auto checkButtonClicked() -> void;
	auto checkButtonHover() -> void;
	auto setMouseCoords() -> void;
	auto resetEvents() -> void;
	auto resetPressed() -> void;
	auto resetHover() -> void;

private:
	GuiManager* gui;

	int mouseX;
	int mouseY;
};

} // end namespace gui

} // end namespace id

#endif
