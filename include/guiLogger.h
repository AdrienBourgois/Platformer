#ifndef GUI_LOGGER_H_INCLUDED
#define GUI_LOGGER_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "logger.h"
#include "guiWindow.h"
#include <string>
#include <array>

namespace id {

class Device;

class DebugLogger
: public GUI_Window
{

public: 
	DebugLogger();
	virtual ~DebugLogger();

	DebugLogger(DebugLogger const&) = delete;
	DebugLogger(DebugLogger&&) = delete;
	auto operator=(DebugLogger const&) -> DebugLogger& = delete;
	auto operator=(DebugLogger&&) -> DebugLogger& = delete;
	
	auto DisplayLog() -> void;
	auto UpdateDebugLog() -> void;
	auto Clear() -> void;
	auto AddLog(const char* ftm, ...) -> void;
	auto DrawLogWindow(const char* tittle) -> void;
	auto CheckboxFilter(std::string filter_build) -> const char*;

private:
	ImGuiTextBuffer buf;
	ImGuiTextFilter	filter;
	ImVector<int>	lineOffsets;
	bool		scrollToBottom;
	std::array<bool, L_COUNT>	arrayCheck;
};

} // namespace id

#endif // GUI_LOGGER_H_INCLUDED

