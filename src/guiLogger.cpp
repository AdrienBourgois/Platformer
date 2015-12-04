#include <SDL2/SDL.h>
#include <iostream>
#include "guiLogger.h"
#include <algorithm>
namespace id {

DebugLogger::DebugLogger()
: GUI_Window(true), scrollToBottom(true) 
{
	std::fill (arrayCheck.begin(), arrayCheck.end(), true);
	UpdateDebugLog();
}

DebugLogger::~DebugLogger()
{
}

auto DebugLogger::UpdateDebugLog() -> void 
{
	for(auto&& val : id::Logger::getInstance()->getBufLogString())
	{
		const char* str = val.c_str();	
		AddLog("%s", str);
	}
	Logger::getInstance()->getBufLogString().clear();
}
auto DebugLogger::Clear() -> void
{
	buf.clear();
	lineOffsets.clear();
}

auto DebugLogger::DisplayLog() -> void
{
	DrawLogWindow("Debug Log");
	UpdateDebugLog();
}

auto DebugLogger::AddLog(const char* ftm, ...) ->void
{
 	int old_size = buf.size();
	va_list args;
	va_start(args, ftm);
	buf.appendv(ftm, args);
	va_end(args);
	for(int new_size = buf.size(); old_size < new_size; ++old_size)
		if(buf[old_size] == '\n')
			lineOffsets.push_back(old_size);
	scrollToBottom = true;	
}

auto DebugLogger::DrawLogWindow(const char* title) ->void 
{
	ImGui::Begin(title, NULL, ImVec2(300, 300));
	{
		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
	

		ImGui::SameLine();
		filter.Draw("Filter",-100.0f);

		ImGui::Separator();

		std::string filter_build = "";
		filter_build = CheckboxFilter(filter_build.c_str());
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += filter.InputBuf;
// filter.InputBuf; // Input dans la barre filter

		auto filter_final = ImGuiTextFilter(filter_build.c_str());	
	
		ImGui::Separator();

		ImGui::BeginChild("scrolling",ImVec2(0,0),false, ImGuiWindowFlags_HorizontalScrollbar);
		{	
			if(copy) ImGui::LogToClipboard();
		
			{
				const char* buf_begin = buf.begin();
				const char* line = buf_begin;
				for(int line_no = 0; line != NULL; ++line_no ) // ou line_no++
				{
					const char* line_end = (line_no < lineOffsets.size()) ? buf_begin + lineOffsets[line_no] : NULL;
					if(filter_final.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
					line = line_end && line_end[1] ? line_end +1 : NULL;
				}
			}
			if (scrollToBottom)
				ImGui::SetScrollHere(1.0f);
			scrollToBottom = false;
		}
		ImGui::EndChild();
	
		ImGui::End();
	}
}

auto DebugLogger::CheckboxFilter(std::string filter_build) -> const char*
{
	ImGui::Checkbox("Error", &arrayCheck[L_ERROR]);
	if(!arrayCheck[L_ERROR])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Error";
	}
	ImGui::SameLine();

	ImGui::Checkbox("Debug", &arrayCheck[L_DEBUG]);
	if(!arrayCheck[L_DEBUG])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Debug";
	}
	
	ImGui::SameLine();

	ImGui::Checkbox("Game", &arrayCheck[L_GAME]);
	if(!arrayCheck[L_GAME])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Game";
	}
	
	ImGui::SameLine();

	ImGui::Checkbox("Info", &arrayCheck[L_INFO]);
	if(!arrayCheck[L_INFO])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Info";
	}
		
	ImGui::SameLine();

	ImGui::Checkbox("Warning", &arrayCheck[L_WARNING]);
	if(!arrayCheck[L_WARNING])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Warning";
	}
		
	ImGui::SameLine();

	ImGui::Checkbox("Loop", &arrayCheck[L_LOOP]);
	if(!arrayCheck[L_LOOP])
	{
		if(!filter_build.empty())
			filter_build += ',';
		filter_build += "-Loop";
	}

	return filter_build.c_str();
}

}//end id 
