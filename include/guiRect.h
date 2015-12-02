#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/gl.h>
#include <vector>
#include <string>
#include <functional>

#include "guiManager.h"
#include "maths/vector.h"

namespace id {
namespace gui {

class GuiRect
{
public:
	GuiRect(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, std::function<void()> func);
	~GuiRect();

	virtual auto createElement(maths::Vector4 color) -> void;
	auto calculateCoordsRect() -> maths::Vector4x2;
	auto addChild(GuiRect* child) -> void;
	virtual auto genVertexObject() -> void;

	auto getParent() const -> GuiRect* { return this->parent; };
	auto getRect() const& -> std::vector<float> { return this->rect; };
	auto getShaderName() const& -> std::string { return this->shaderName; };
	auto getType() const -> std::string { return this->type; };
	auto getPosX() const -> float { return this->posX; };
	auto getPosY() const -> float { return this->posY; };
	auto getWidth() const -> float { return this->width; };
	auto getHeight() const -> float { return this->height; };
	auto getColorBg() const -> maths::Vector4 { return this->colorBg; };
	auto getVao() const -> GLuint { return this->vao; };
	auto getVbo() const -> GLuint { return this->vbo; };
	auto getTexID() const -> GLuint { return this->texID; };
	auto getID() const -> int { return this->id; };
	auto getVisible() const -> bool { return this->visible; };
	auto getListenEvent() const -> bool { return this->listenEvent; };
	auto getPressed() const -> bool { return this->pressed; };
	auto getFunc() -> std::function<void()> { return this->func; };

	auto setListenEvent(bool listen) -> void { this->listenEvent = listen; };
	auto setPressed(bool press) -> void { this->pressed = press; };

protected:
	GuiManager* gui;
	GuiRect* parent;
	std::vector<GuiRect*> children;
	std::vector<float> rect;
	std::string shaderName;
	std::string type;

	float posX, posY;
	float width, height;
	maths::Vector4 colorBg;
	GLuint vao;
	GLuint vbo;
	GLuint texID;
	int id;
	bool visible;
	bool listenEvent;

	bool pressed;
	std::function<void()> func;
};

} // end namespace

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
