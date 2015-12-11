#ifndef LEVELEDITORELEMENT_H_INCLUDED
#define MENULEVELEDITORELEMENT_H_INCLUDED

#include "imgui.h"
#include "imgui_impl.h"
#include "device.h" 
namespace id {

class LevelEditorElement
{
public:
	LevelEditorElement(Device* dev);
	virtual	~LevelEditorElement();
	
	virtual	auto Display() -> void = 0;
	virtual auto Display(Device* dev) ->void = 0;
protected:
	Device*	dev;
	bool visible;
};


} //end id 
#endif
