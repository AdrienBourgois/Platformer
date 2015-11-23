#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/glew.h>

#include "sceneManager.h"
#include "sceneNode.h"
#include "maths/vector.h"

namespace id {
namespace gui {

class GuiManager;

class GuiRect
{
public:
	GuiRect(GuiManager* gui, maths::Vector4 color);
	~GuiRect();

	auto getColor() const -> maths::Vector4 { return this->color; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getRect() const -> std::vector<GLfloat> { return this->rect; };

private:
	std::vector<GLfloat> rect;
	maths::Vector4 color;
	GLuint vao;
	GLuint vbo;
};

} // end namespace gui

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
