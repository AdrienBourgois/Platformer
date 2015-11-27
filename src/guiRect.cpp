#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include "guiRect.h"
#include "guiManager.h"
#include "maths/vector.h"
#include "txtLogger.h"

#include <iostream>

namespace {
    id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiRect::GuiRect(GuiManager* gui)
: gui(gui), pos({0.f, 0.f}), width(0), height(0), color({0.f, 0.f, 0.f, 0.f}), vao(0), vbo(0), texID(0), id(-1), isPressed(false), hover(false), visible(false)
{
	logger->log("Creating Gui...", LL_INFO);

	logger->log("Gui created", LL_INFO);
}
GuiRect::~GuiRect()
{
	logger->log("Deleting GuiRect...", LL_INFO);

	this->gui = nullptr;
	this->parent = nullptr;
	glDeleteVertexArrays(1, &this->vao);
	this->vao = 0;
	glDeleteBuffers(1, &this->vbo);
	this->vbo = 0;
	glDeleteTextures(1, &this->texID);

	logger->log("GuiRect deleted", LL_INFO);
}
auto GuiRect::createRect(GuiRect* parent, maths::Vector2 pos, float width, float height, maths::Vector4 color, bool visible, int id) -> void
{
	stockParameters(parent, visible, pos, width, height, color, id);
	maths::Vector4x2 coordsRect = calculatePosCornerRect(pos, width, height);

	this->rect =
	{
		coordsRect.val[0][0], coordsRect.val[0][1], color.val[0], color.val[1], color.val[2], color.val[3],
		coordsRect.val[1][0], coordsRect.val[1][1], color.val[0], color.val[1], color.val[2], color.val[3],
		coordsRect.val[2][0], coordsRect.val[2][1], color.val[0], color.val[1], color.val[2], color.val[3],
		coordsRect.val[2][0], coordsRect.val[2][1], color.val[0], color.val[1], color.val[2], color.val[3],
		coordsRect.val[3][0], coordsRect.val[3][1], color.val[0], color.val[1], color.val[2], color.val[3],
		coordsRect.val[0][0], coordsRect.val[1][1], color.val[0], color.val[1], color.val[2], color.val[3],
	};

	createVertexObject();
}
auto GuiRect::createButton(GuiRect* parent, maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text, bool visible, int id) -> void
{
	stockParameters(parent, visible, pos, width, height, colorBg, id);
	maths::Vector4x2 coordsRect = calculatePosCornerRect(pos, width, height);

	this->rect =
    {
        coordsRect.val[0][0], coordsRect.val[0][1], 1.f, 0.f,
        coordsRect.val[1][0], coordsRect.val[1][1], 0.f, 0.f,
        coordsRect.val[2][0], coordsRect.val[2][1], 0.f, 1.f,
        coordsRect.val[2][0], coordsRect.val[2][1], 0.f, 1.f,
        coordsRect.val[3][0], coordsRect.val[3][1], 1.f, 1.f,
        coordsRect.val[0][0], coordsRect.val[0][1], 1.f, 0.f
    };
	
	createText(text, colorText);
	createVertexObject();
}
auto GuiRect::createText(std::string const& text, maths::Vector4 colorText) -> void
{
	SDL_Color color = { (Uint8)(colorText.val[0] * 255), (Uint8)(colorText.val[1] * 255), (Uint8)(colorText.val[2] * 255), (Uint8)(colorText.val[3] * 255) };
	SDL_Surface* surf = TTF_RenderText_Blended(this->gui->getFont(), (" " + text + " ").c_str(), color);
	SDL_assert(surf);

	glGenTextures(1, &this->texID);
	glBindTexture(GL_TEXTURE_2D, this->texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}
auto GuiRect::createVertexObject() -> void
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(GLfloat), &this->rect[0], GL_STATIC_READ);

	if (this->texID == 0)
		vertexAttributesRect();
	else
		vertexAttributesButton();

	glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
auto GuiRect::vertexAttributesRect() -> void
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
auto GuiRect::vertexAttributesButton() -> void
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
auto GuiRect::calculatePosCornerRect(maths::Vector2 pos, float width, float height) -> maths::Vector4x2
{
	float posX = (this->parent) ? pos.val[0] + this->parent->getPos().val[0] : pos.val[0];
	float posY = (this->parent) ? pos.val[1] + this->parent->getPos().val[1] : pos.val[1];
	float upRightX = posX + (width/2);
    float upRightY = -(posY + (height/2));
    float upLeftX = posX - (width/2);
    float upLeftY = -(posY + (height/2));
    float downLeftX = posX - (width/2);
    float downLeftY = -(posY - (height/2));
    float downRightX = posX + (width/2);
    float downRightY = -(posY - (height/2));

	return { upRightX, upRightY, upLeftX, upLeftY, downLeftX, downLeftY, downRightX, downRightY };
}
auto GuiRect::stockParameters(GuiRect* parent, bool visible, maths::Vector2 pos, float width, float height, maths::Vector4 color, int id) -> void
{
	if (parent)
	{
		this->parent = parent;
		parent->addChild(this);
		if (parent->getVisible())
			this->visible = visible;
		else
			this->visible = false;
	}
    else
    {
        this->parent = this->gui->getRootGui();
        this->visible = visible;
    }
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->color = color;
	this->id = id;
}
auto GuiRect::addChild(GuiRect* child) -> void
{
	this->children.push_back(child);
}
auto GuiRect::setVisible(bool visible) -> void
{
	this->visible = visible;
	for (std::vector<GuiRect*>::iterator it = this->children.begin(); it != this->children.end(); ++it)
	{
		(*it)->setVisible(visible);
	}
}

} // end namespace gui

} // end namespace id
