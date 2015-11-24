#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#include "maths/vector.h"
#include "guiRect.h"
#include "sceneManager.h"
#include "window.h"

namespace id {
namespace gui {

class GuiEventReceiver;

class GuiManager
{
public:
	GuiManager(int widthWin, int heightWin);
	~GuiManager();

	auto initGui() -> void;
	auto renderGui() -> void;
	auto createShader(std::string const& name, GLint shaderType) -> GLuint;
	auto createProgram(std::string const& pathShader) -> GLuint;
	auto addToRender(GuiRect* rect) -> void;

	auto addRect(maths::Vector2 pos, float width, float height, maths::Vector4 color) -> void;
	auto addButton(maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text) -> void;

	auto getRenderedRect() -> std::vector<GuiRect*>& { return this->renderedRect; };
	auto getGuiEvt() const -> GuiEventReceiver* { return this->guiEvt; };
	auto getFont() const -> TTF_Font* { return this->font; };
	auto getWidthWin() const -> int { return this->widthWin; };
	auto getHeightWin() const -> int { return this->heightWin; };

private:
	std::vector<GuiRect*> renderedRect;
	GuiEventReceiver* guiEvt;

	GLuint prgIDRect;
	GLuint prgIDButton;
	GLuint proj;
	TTF_Font* font;

	int widthWin;
	int heightWin;
};

} // end namespace gui

} // end namespace id

#endif // GUI_H_INCLUDED
