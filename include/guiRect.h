#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/gl.h>
#include <vector>
#include <string>

#include "guiManager.h"
#include "maths/vector.h"

namespace id {
namespace gui {

class GuiRect
{
public:
	GuiRect(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible);
	~GuiRect();

	virtual auto createElement(maths::Vector4 color) -> void;
	auto calculateCoordsRect() -> maths::Vector4x2;
	virtual auto genVertexObject() -> void;

	auto getParent() const -> GuiRect* { return this->parent; };
	auto getRect() -> std::vector<float>* { return &this->rect; };
	auto getShaderName() -> std::string* { return &this->shaderName; };
	auto getPosX() const -> float { return this->posX; };
	auto getPosY() const -> float { return this->posY; };
	auto getWidth() const -> float { return this->width; };
	auto getHeight() const -> float { return this->height; };
	auto getColorBg() const -> maths::Vector4 { return this->colorBg; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getID() const -> int { return this->id; };
	auto getVisible() const -> bool { return this->visible; };

private:
	GuiManager* gui;
	GuiRect* parent;
	std::vector<GuiRect*> children;
	std::vector<float> rect;
	std::string shaderName;

	float posX, posY;
	float width, height;
	maths::Vector4 colorBg;
	GLuint vao;
	GLuint vbo;
	int id;
	bool visible;
};

} // end namespace

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
