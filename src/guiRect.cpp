#include <GL/glew.h>
#include <vector>
#include <functional>

#include "txtLogger.h"
#include "guiRect.h"
#include "guiManager.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiRect::GuiRect(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, std::function<void()> func)
: gui(gui), parent(parent), shaderName(""), type(""), posX(posX), posY(posY), width(width), height(height), colorBg({0.f, 0.f, 0.f, 0.f}), vao(0), vbo(0), texID(0), id(id), visible(visible), listenEvent(false), pressed(false), func(func)
{
	logger->log("Creating GuiRect...", LL_INFO);

	if (parent)
	{
		parent->addChild(this);
	}
	else
	{
		this->parent = gui->getRoot();
	}

	logger->log("GuiRect created", LL_INFO);
}
GuiRect::~GuiRect()
{
	logger->log("Deleting GuiRect...", LL_INFO);

	logger->log("GuiRect deleted", LL_INFO);
}
auto GuiRect::createElement(maths::Vector4 color) -> void
{
	this->shaderName = "pos2d_color4";
	this->type = "rect";
	this->colorBg = color;
	maths::Vector4x2 coordsRect = calculateCoordsRect();
	this->rect = {
		coordsRect.val[0][0], coordsRect.val[0][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
        coordsRect.val[1][0], coordsRect.val[1][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
        coordsRect.val[2][0], coordsRect.val[2][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
        coordsRect.val[2][0], coordsRect.val[2][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
        coordsRect.val[3][0], coordsRect.val[3][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
        coordsRect.val[0][0], coordsRect.val[0][1], this->colorBg.val[0], this->colorBg.val[1], this->colorBg.val[2], this->colorBg.val[3],
	};
	genVertexObject();
}
auto GuiRect::calculateCoordsRect() -> maths::Vector4x2
{
	float posX = (this->parent) ? this->posX + this->parent->getPosX() : this->posX;
	float posY = (this->parent) ? this->posY + this->parent->getPosY() : this->posY;
	float upRightX = posX + (this->width/2);
	float upRightY = -(posY + (this->height/2));
	float upLeftX = posX - (this->width/2);
	float upLeftY = -(posY + (this->height/2));
	float downLeftX = posX - (this->width/2);
	float downLeftY = -(posY - (this->height/2));
	float downRightX = posX + (this->width/2);
	float downRightY = -(posY - (this->height/2));

	return {upRightX, upRightY, upLeftX, upLeftY, downLeftX, downLeftY, downRightX, downRightY};
}
auto GuiRect::addChild(GuiRect* child) -> void
{
	this->children.push_back(child);
}
auto GuiRect::genVertexObject() -> void
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(float), &this->rect[0], GL_STATIC_READ);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
auto GuiRect::setVisible(bool visible) -> void
{
	this->visible = visible;
	for (auto it = this->children.begin(); it != this->children.end(); ++it)
		(*it)->setVisible(visible);
}

} // end namespace gui

} // end namespace id
