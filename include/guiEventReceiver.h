#ifndef GUI_EVENT_RECEIVER_H_INCLUDED
#define GUI_EVENT_RECEIVER_H_INCLUDED

#include <SDL2/SDL.h>

#include "guiManager.h"

namespace id {
namespace gui {

class GuiManager;

class GuiEventReceiver
{
public:
	GuiEventReceiver(GuiManager* gui);
	~GuiEventReceiver();
	GuiEventReceiver(GuiEventReceiver const&) = delete;
	GuiEventReceiver(GuiEventReceiver&&) = delete;
	auto operator=(GuiEventReceiver const&) = delete;
	auto operator=(GuiEventReceiver&&) = delete;

	auto eventListener(SDL_Event* ev) -> void;
	auto checkMouseOnButton() -> void;
	auto listenNextKey(SDL_Event* ev) -> void;
	auto changeResolution() -> void;
	auto refreshMouseCoords() -> void;
	auto resetEvents() -> void;

	auto setListenKeys(bool listen) -> void { this->listenKeys = listen; }

private:
	GuiManager* gui;
	int mouseX, mouseY;
	bool listenKeys;
};

} // namespace 

} // namespace id

#endif // GUI_EVENT_RECEIVER_H_INCLUDED
