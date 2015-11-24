#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/glew.h>
#include <string>

#include "sceneManager.h"
#include "sceneNode.h"
#include "maths/vector.h"

namespace id {
namespace gui {

class GuiManager;

class GuiRect
{
public:
	GuiRect();
	~GuiRect();

	auto createRect(maths::Vector2 pos, float width, float height, maths::Vector4 color) -> void;
	auto createButton(GuiManager* gui, maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text) -> void;
	auto createText(GuiManager* gui, std::string const& text, maths::Vector4 colorText) -> void;
	auto createVertexObject() -> void;
	auto vertexAttributesRect() -> void;
	auto vertexAttributesButton() -> void;

	auto getColor() const -> maths::Vector4 { return this->color; };
	auto getPos() const -> maths::Vector2 { return this->pos; };
	auto getWidth() const -> float { return this->width; };
	auto getHeight() const -> float { return this->height; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getRect() const -> std::vector<GLfloat> { return this->rect; };
	auto getTexID() const -> GLuint { return this->texID; };

	auto setIsPressed(bool pressed) -> void { this->isPressed = pressed; };

private:
	std::vector<GLfloat> rect;
	maths::Vector2 pos;
	float width;
	float height;
	maths::Vector4 color;
	GLuint vao;
	GLuint vbo;
	GLuint texID;

	bool isPressed;
};

} // end namespace gui

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
