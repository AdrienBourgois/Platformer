#include "levelEditor.h"
#include "leveleditor/menuLevelEditor.h"
#include "logger.h"
#include "new"

namespace id {

LevelEditor::LevelEditor(Device* device)
:dev(device)
{
	LOG(L_INFO, "Creating LevelEditor...");
	menuLevelEditor = new (std::nothrow) MenuLevelEditor(device);		
	dev = device;
}

LevelEditor::~LevelEditor()
{
	LOG(L_INFO, "Destructing LevelEditor...");
}

auto LevelEditor::InitLevelEditor() -> void
{
}

auto LevelEditor::DisplayLevelEditor() -> void
{
	menuLevelEditor->Display();
}

auto LevelEditor::UpdateLevelEditor() -> void
{
}

}// end id
