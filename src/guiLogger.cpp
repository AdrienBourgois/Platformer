#include <SDL2/SDL.h>
#include <iostream>
#include "guiLogger.h"

namespace id {

DebugLogger::DebugLogger()
: GUI_Window(true), scrollToBottom(true) 
{
	std::cout<< "Created DebuLogger()"<< std::endl;
	bool checkError = false;
	bool checkInfo = false;
	bool checkGame = false;
	bool checkWarning = false;
	bool checkDebug = false;
	mapCheck.insert(std::pair<std::string, bool>("Error",checkError));
	mapCheck.insert(std::pair<std::string, bool>("Info",checkInfo));
	mapCheck.insert(std::pair<std::string, bool>("Game",checkGame));
	mapCheck.insert(std::pair<std::string, bool>("Warning",checkWarning));
	mapCheck.insert(std::pair<std::string, bool>("Debug",checkDebug));
	UpdateDebugLog();
}

DebugLogger::~DebugLogger()
{
	std::cout << "Destructor " <<std::endl;
}

auto DebugLogger::UpdateDebugLog() -> void 
{
	std::vector<std::string>::iterator it = id::Logger::getInstance()->getBufLogString().begin();
	std::vector<std::string>::iterator itE = id::Logger::getInstance()->getBufLogString().end();

	for(; it != itE; ++it)
	{
		const char* str = it->c_str();	
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
	// add bouton is clicked par ici
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
	//	ImGui::SameLine();
		ImGui::Checkbox("Error", &mapCheck.find("Error")->seconde);
		{
			if(mapCheck.find("Error")->seconde == false)
				std::cout<< "test"<< std::endl; 
		}
		ImGui::SameLine();
	
		ImGui::Checkbox("Debug", &mapCheck.find("Debug")->seconde);
		{
			if(check1 == false)
				std::cout<< "test"<< std::endl; 
		}	
		ImGui::SameLine();
	
		static bool check2 = false;
		ImGui::Checkbox("Game", &check);
		ImGui::Checkbox("Error", &mapCheck.find("Error")->seconde);
		{
		{
			if(check2 == true)
				std::cout<< "test"<< std::endl; 
		}	
		ImGui::SameLine();
	
		static bool check3 = false;
		ImGui::Checkbox("Info", &check);
		ImGui::Checkbox("Error", &mapCheck.find("Error")->seconde);
		{
		{
			if(check3 == true)
				std::cout<< "test"<< std::endl; 
		}	
		ImGui::SameLine();
	
		static bool check4 = false;
		ImGui::Checkbox("Warning", &check);
		ImGui::Checkbox("Error", &mapCheck.find("Error")->seconde);
		{
		{
			if(check4 == true)
				std::cout<< "test"<< std::endl; 
		}	

		ImGui::Separator();

		ImGui::BeginChild("scrolling",ImVec2(0,0),false, ImGuiWindowFlags_HorizontalScrollbar);
		{	
			if (copy) ImGui::LogToClipboard();
	
			if (filter.IsActive())
			{
				const char* buf_begin = buf.begin();
				const char* line = buf_begin;
				for(int line_no = 0; line != NULL; ++line_no ) // ou line_no++
				{
					const char* line_end = (line_no < lineOffsets.size()) ? buf_begin + lineOffsets[line_no] : NULL;
					if(filter.PassFilter(line, line_end))
					ImGui::TextUnformatted(line, line_end);
					line = line_end && line_end[1] ? line_end +1 : NULL;
				}
			}
			else
			{
				ImGui::TextUnformatted(buf.begin());
			}
			if (scrollToBottom)
				ImGui::SetScrollHere(1.0f);
			scrollToBottom = false;
		}
		ImGui::EndChild();
	
		ImGui::End();
	}
}
}//end id 
