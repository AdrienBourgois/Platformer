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

GuiRect::GuiRect()
: pos({0.f, 0.f}), width(0), height(0), color({0.f, 0.f, 0.f, 0.f}), vao(0), vbo(0), texID(0), isPressed(false) 
{
	logger->log("Creating Gui...", LL_INFO);

	logger->log("Gui created", LL_INFO);
}
GuiRect::~GuiRect()
{
	logger->log("Deleting GuiRect...", LL_INFO);

	glDeleteVertexArrays(1, &this->vao);
	this->vao = 0;
	glDeleteBuffers(1, &this->vbo);
	this->vbo = 0;
	glDeleteTextures(1, &this->texID);

	logger->log("GuiRect deleted", LL_INFO);
}
auto GuiRect::createRect(maths::Vector2 pos, float width, float height, maths::Vector4 color) -> void
{
	float cornerUpRightX = pos.val[0] + (width/2);
	float cornerUpRightY = -(pos.val[1] + (height/2));
	float cornerUpLeftX = pos.val[0] - (width/2);
	float cornerUpLeftY = -(pos.val[1] + (height/2));
	float cornerDownLeftX = pos.val[0] - (width/2);
	float cornerDownLeftY = -(pos.val[1] - (height/2));
	float cornerDownRightX = pos.val[0] + (width/2);
	float cornerDownRightY = -(pos.val[1] - (height/2));

	this->rect =
	{
		cornerUpRightX, cornerUpRightY, color.val[0], color.val[1], color.val[2], color.val[3],
		cornerUpLeftX, cornerUpLeftY, color.val[0], color.val[1], color.val[2], color.val[3],
		cornerDownLeftX, cornerDownLeftY, color.val[0], color.val[1], color.val[2], color.val[3],
		cornerDownLeftX, cornerDownLeftY, color.val[0], color.val[1], color.val[2], color.val[3],
		cornerDownRightX, cornerDownRightY, color.val[0], color.val[1], color.val[2], color.val[3],
		cornerUpRightX, cornerUpRightY, color.val[0], color.val[1], color.val[2], color.val[3],
	};
	this->pos = pos;
	this->width = width;
	this->height = height;
	this->color = color;
	createVertexObject();
}
auto GuiRect::createButton(GuiManager* gui, maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text) -> void
{
	float cornerUpRightX = pos.val[0] + (width/2);
    float cornerUpRightY = -(pos.val[1] + (height/2));
    float cornerUpLeftX = pos.val[0] - (width/2);
    float cornerUpLeftY = -(pos.val[1] + (height/2));
    float cornerDownLeftX = pos.val[0] - (width/2);
    float cornerDownLeftY = -(pos.val[1] - (height/2));
    float cornerDownRightX = pos.val[0] + (width/2);
    float cornerDownRightY = -(pos.val[1] - (height/2));

	this->rect =
    {
        cornerUpRightX, cornerUpRightY, 1.f, 0.f,
        cornerUpLeftX, cornerUpLeftY, 0.f, 0.f,
        cornerDownLeftX, cornerDownLeftY, 0.f, 1.f,
        cornerDownLeftX, cornerDownLeftY, 0.f, 1.f,
        cornerDownRightX, cornerDownRightY, 1.f, 1.f,
        cornerUpRightX, cornerUpRightY, 1.f, 0.f
    };
	this->pos = pos;
	this->width = width;
	this->height = height;
	this->color = colorBg;
	
	createText(gui, text, colorText);
	createVertexObject();
}
auto GuiRect::createText(GuiManager* gui, std::string const& text, maths::Vector4 colorText) -> void
{
	SDL_Color color = { (Uint8)(colorText.val[0] * 255), (Uint8)(colorText.val[1] * 255), (Uint8)(colorText.val[2] * 255), (Uint8)(colorText.val[3] * 255) };
	SDL_Surface* surf = TTF_RenderText_Blended(gui->getFont(), text.c_str(), color);
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

} // end namespace gui

} // end namespace id
