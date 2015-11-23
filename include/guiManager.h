#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "maths/vector.h"
#include "guiRect.h"
#include "sceneManager.h"
#include "window.h"

namespace id {
namespace gui {

class GuiManager
{
public:
	GuiManager(std::unique_ptr<Window>::pointer win, scene::SceneManager* scn);
	~GuiManager();

	auto initGui() -> void;
	auto renderGui() -> void;
	auto createShader(std::string const& name, GLint shaderType) -> GLuint;
	auto createProgram(std::string const& pathShader) -> GLuint;
	auto addButton(maths::Vector2 pos, int width, int height) -> void;
	auto addToRender(GuiRect* rect) -> void;

private:
	std::vector<GuiRect*> renderedRect;

	GLuint prgID;
	GLuint proj;
	float x;

	std::unique_ptr<Window> win;
	scene::SceneManager* scn;
};

} // end namespace gui

} // end namespace id

#endif // GUI_H_INCLUDED
