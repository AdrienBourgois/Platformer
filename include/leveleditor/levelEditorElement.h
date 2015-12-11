#ifndef LEVEL_EDITOR_ELEMENT_H_INCLUDED
#define LEVEL_EDITOR_ELEMENT_H_INCLUDED

namespace id {

class Device;

class LevelEditorElement
{
public:
	LevelEditorElement(Device* dev);
	virtual	~LevelEditorElement();
	LevelEditorElement(LevelEditorElement const&) = delete;
	LevelEditorElement(LevelEditorElement&&) = delete;
	auto operator=(LevelEditorElement const&) -> LevelEditorElement& = delete;
	auto operator=(LevelEditorElement&&) -> LevelEditorElement& = delete;
	
	virtual	auto Display() -> void = 0;
	virtual auto Display(Device* dev) ->void = 0;

protected:
	Device*	dev;
	bool visible;
};


} // namespace id 

#endif // LEVEL_EDITOR_ELEMENT_H_INCLUDED
