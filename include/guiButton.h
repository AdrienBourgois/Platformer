#ifndef GUI_BUTTON_H_INCLUDED
#define GUI_BUTTON_H_INCLUDED

#include <string>
#include <functional>

#include "guiManager.h"
#include "guiRect.h"

namespace id {
namespace gui {

class GuiButton : public GuiRect
{
public:
	GuiButton(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, std::function<void()> func);
	~GuiButton();

	virtual auto createElement(maths::Vector4 colorBg, std::string const& text, maths::Vector4 colorText) -> void;
	virtual auto genVertexObject() -> void;

	auto getText() const -> std::string const& { return this->text; };
	auto getNewText() const -> std::string const& { return this->newText; };
	auto getColorText() const -> maths::Vector4 { return this->colorText; };

	auto setText(std::string const& text) -> void { this->text = text; }; 
	auto setNewText(std::string const& text) -> void { this->newText = text; }; 

private:
	std::string text;
	std::string newText;
	maths::Vector4 colorText;
};

} // end namespace gui

} // end namespace id

#endif // GUI_BUTTON_H_INCLUDED
