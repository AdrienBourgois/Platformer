#ifndef GUI_LOGGER_H_INCLUDED
#define GUI_LOGGER_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "logger.h"
#include "guiWindow.h"
#include <vector>
#include <string>
#include <map>
#include <array>

namespace id {

class Device;

class DebugLogger: public GUI_Window
{

public: 
	DebugLogger();
	~DebugLogger();
	
	auto DisplayLog() ->void;
	auto UpdateDebugLog() ->void;
	auto Clear()-> void;
	auto AddLog(const char* ftm, ...) ->void;
	auto DrawLogWindow(const char* tittle)-> void;

private:

	ImGuiTextBuffer buf;
	ImGuiTextFilter	filter;
	ImVector<int>	lineOffsets;
	bool		scrollToBottom;
	std::array<bool, L_COUNT>	arrayCheck;
};

} // id

#endif

