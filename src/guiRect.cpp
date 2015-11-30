#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>

#include "txtLogger.h"
#include "guiRect.h"
#include "guiManager.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiRect::GuiRect(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible)
: gui(gui), parent(parent), posX(posX), posY(posY), width(width), height(height), color({0.f, 0.f, 0.f, 0.f}), id(id), visible(visible)
{
	logger->log("Creating GuiRect...", LL_INFO);

	SDL_assert(gui);

	logger->log("GuiRect created", LL_INFO);
}
GuiRect::~GuiRect()
{
	logger->log("Deleting GuiRect...", LL_INFO);

	logger->log("GuiRect deleted", LL_INFO);
}
auto GuiRect::createRect(maths::Vector4 color) -> void
{
	this->color = color;
	calculateCoordsRect();
	genVertexObject();
}
auto GuiRect::calculateCoordsRect() -> void
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
	this->rect = {
		upRightX, upRightY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
		upLeftX, upLeftY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
		downLeftX, downLeftY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
		downLeftX, downLeftY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
		downRightX, downRightY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
		upRightX, upRightY, this->color.val[0], this->color.val[1], this->color.val[2], this->color.val[3],
	};
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
}

} // end namespace gui

} // end namespace id
