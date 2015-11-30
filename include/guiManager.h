#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include <GL/gl.h>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "maths/matrix.h"

namespace id {
namespace gui {

class GuiRect;

class GuiManager
{
public:
	~GuiManager();
	GuiManager(GuiManager const&) = delete;
	GuiManager(GuiManager&&) = delete;
	GuiManager& operator = (GuiManager const&) = delete;
	GuiManager& operator = (GuiManager&&) = delete;

	static auto createGuiManager(int windowWidth, int windowHeight) -> std::unique_ptr<GuiManager>;
	auto render() -> void;

	auto addRect(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, maths::Vector4 color) -> void;
	auto addToRender(GuiRect* newRect) -> void;

	auto loadProgram(std::string const& nameShader) -> void;
	auto loadShader(std::string const& name, GLint shaderType) -> GLuint;

private:
	GuiManager(int windowWidth, int windowHeight);
	std::vector<GuiRect*> drawRect;
	std::map<std::string, GLuint> programGui;

	int windowWidth, windowHeight;
	std::array<float, 16> camOrtho;
	GuiRect* root;
};

} // end namespace gui

} // end namespace id

#endif // GUI_MANAGER_H_INCLUDED
