#include "leveleditor/levelEditorElement.h"
#include "logger.h"


namespace id {

LevelEditorElement::LevelEditorElement(Device* device)
:dev(device)
{
	LOG(L_INFO,"Creating LevelEditorElement");
	visible = true;
}

LevelEditorElement::~LevelEditorElement()
{
	LOG(L_INFO,"Destructing LevelEditorElement");
}


}//end id
