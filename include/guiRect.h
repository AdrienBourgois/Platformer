#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/glew.h>
#include <string>

#include "maths/vector.h"

namespace id {
namespace gui {

class GuiManager;

class GuiRect
{
public:
	GuiRect(GuiManager* gui);
	~GuiRect();

	auto createRect(GuiRect* parent, maths::Vector2 pos, float width, float height, maths::Vector4 color, bool visible) -> void;
	auto createButton(GuiRect* parent, maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text, bool visible, int id) -> void;
	auto createText(std::string const& text, maths::Vector4 colorText) -> void;
	auto createVertexObject() -> void;
	auto vertexAttributesRect() -> void;
	auto vertexAttributesButton() -> void;
	auto calculatePosCornerRect(maths::Vector2 pos, float width, float height) -> maths::Vector4x2;
	auto stockParameters(GuiRect* parent, bool visible, maths::Vector2 pos, float width, float height, maths::Vector4 color) -> void;

	auto addChild(GuiRect* child) -> void;

	auto getParent() const -> GuiRect* { return this->parent; };
	auto getColor() const -> maths::Vector4 { return this->color; };
	auto getPos() const -> maths::Vector2 { return this->pos; };
	auto getWidth() const -> float { return this->width; };
	auto getHeight() const -> float { return this->height; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getRect() const -> std::vector<GLfloat> { return this->rect; };
	auto getTexID() const -> GLuint { return this->texID; };
	auto getID() const -> int { return this->id; };
	auto getIsPressed() const -> bool { return this->isPressed; };
	auto getHover() const -> bool { return this->hover; };
	auto getVisible() const -> bool { return this->visible; };

	auto setIsPressed(bool pressed) -> void { this->isPressed = pressed; };
	auto setHover(bool hover) -> void { this->hover = hover; };
	auto setVisible(bool visible) -> void;

private:
	GuiManager* gui;
	GuiRect* parent;
	std::vector<GuiRect*> children;
	std::vector<GLfloat> rect;
	maths::Vector2 pos;
	float width;
	float height;
	maths::Vector4 color;
	GLuint vao;
	GLuint vbo;
	GLuint texID;

	int id;
	bool isPressed;
	bool hover;
	bool visible;
};

} // end namespace gui

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
