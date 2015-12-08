#include "levelEditor.h"
#include "leveleditor/menuLevelEditor.h"
//#include "leveleditor/addButtonLevelEditor.h"
//#include "leveleditor/"
#include "logger.h"
#include "new"

namespace id {

LevelEditor::LevelEditor()
: GUI_Window(true)
{
	LOG(L_INFO, "Creating LevelEditor...");
}

LevelEditor::~LevelEditor()
{
	LOG(L_INFO, "Destructing LevelEditor...");
}

auto LevelEditor::InitLevelEditor() -> void
{
	menuLevelEditor = new (std::nothrow) MenuLevelEditor();		
}

auto LevelEditor::DisplayLevelEditor() -> void
{
	menuLevelEditor->Display();
}

auto LevelEditor::UpdateLevelEditor() -> void
{
}

}// end id
