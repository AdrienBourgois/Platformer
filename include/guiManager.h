#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>

#include "maths/vector.h"
#include "guiRect.h"

namespace id {
namespace gui {

class GuiManager
{
public:
	~GuiManager();

	auto initGui(SDL_Window* window) -> void;
	auto renderGui() -> void;
	auto addButton(maths::Vector2 pos, int width, int height) -> void;
	auto addToRender(GuiRect* rect) -> void;

private:
	GuiManager();

	std::vector<GuiRect*> renderedRect;

	GLuint prgID;
	GLuint vao;
	GLuint vbo;
	GLuint proj;

	int widthWindow;
	int heightWindow;
};

} // end namespace gui

} // end namespace id

#endif // GUI_H_INCLUDED
