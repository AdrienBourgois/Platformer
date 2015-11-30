#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/gl.h>
#include <vector>

#include "guiManager.h"
#include "maths/vector.h"

namespace id {
namespace gui {

class GuiRect
{
public:
	GuiRect(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible);
	~GuiRect();

	auto createRect(maths::Vector4 color) -> void;
	auto calculateCoordsRect() -> void;
	virtual auto genVertexObject() -> void;

	auto getParent() const -> GuiRect* { return this->parent; };
	auto getPosX() const -> float { return this->posX; };
	auto getPosY() const -> float { return this->posY; };
	auto getWidth() const -> float { return this->width; };
	auto getHeight() const -> float { return this->height; };
	auto getColor() const -> maths::Vector4 { return this->color; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getID() const -> int { return this->id; };
	auto getVisible() const -> bool { return this->visible; };

private:
	GuiManager* gui;
	GuiRect* parent;
	std::vector<GuiRect*> children;
	std::vector<float> rect;

	float posX, posY;
	float width, height;
	maths::Vector4 color;
	GLuint vao;
	GLuint vbo;
	int id;
	bool visible;
};

} // end namespace

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
