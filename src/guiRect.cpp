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

	this->gui = nullptr;
	this->parent = nullptr;
	this->children.clear();
	this->rect.clear();
	glDeleteVertexArrays(1, &this->vao);
	this->vao = 0;
	glDeleteBuffers(1, &this->vbo);
	this->vbo = 0;
	glDeleteTextures(1, &this->texID);
	this->texID = 0;
	this->func = nullptr;

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
	this->posX = posX;
	float posY = (this->parent) ? this->posY + this->parent->getPosY() : this->posY;
	this->posY = posY;
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
auto GuiRect::addGradient(maths::Vector4 colorStart, maths::Vector4 colorStop) -> void
{
	this->rect[2] = this->rect[26] = this->rect[32] = colorStop.val[0];
	this->rect[3] = this->rect[27] = this->rect[33] = colorStop.val[1];
	this->rect[4] = this->rect[28] = this->rect[34] = colorStop.val[2];
	this->rect[5] = this->rect[29] = this->rect[35] = colorStop.val[3];
	this->rect[8] = this->rect[14] = this->rect[20] = colorStart.val[0];
	this->rect[9] = this->rect[15] = this->rect[21] = colorStart.val[1];
	this->rect[10] = this->rect[16] = this->rect[22] = colorStart.val[2];
	this->rect[11] = this->rect[17] = this->rect[23] = colorStart.val[3];

	glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(float), &this->rect[0], GL_STATIC_READ);

	glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
auto GuiRect::refreshRect(float posX, float posY, float width, float height) -> void
{
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;

	maths::Vector4x2 coords = calculateCoordsRect();

	this->rect[0] = this->rect[30] = coords.val[0][0];
	this->rect[1] = this->rect[31] = coords.val[0][1];
	this->rect[6] = coords.val[1][0];
	this->rect[7] = coords.val[1][1];
	this->rect[12] = this->rect[18] = coords.val[2][0];
	this->rect[13] = this->rect[19] = coords.val[2][1];
	this->rect[24] = coords.val[3][0];
	this->rect[25] = coords.val[3][1];

	glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(float), &this->rect[0], GL_STATIC_READ);

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
