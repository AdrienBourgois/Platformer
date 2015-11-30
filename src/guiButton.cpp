#include <GL/glew.h>
#include <string>

#include "txtLogger.h"
#include "guiButton.h"
#include "guiRect.h"
#include "guiManager.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiButton::GuiButton(GuiManager* gui, GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible)
: GuiRect(gui, parent, posX, posY, width, height, id, visible)
{
	logger->log("Creating Button...", LL_INFO);

	logger->log("Button created", LL_INFO);
}
GuiButton::~GuiButton()
{
	logger->log("Deleting Button...", LL_INFO);

	logger->log("Button deleted", LL_INFO);
}
auto createElement(maths::Vector4 colorBg, std::string const& text, maths::Vector4 colorText) -> void
{
	this->shaderName = "pos2d_tex2d_color4";
	this->colorBg = colorBg;
	maths::Vector4x2 coordsRect = calculateCoordsRect();
	this->rect = {
		coordsRect.val[0][0], coordsRect.val[0][1], 1.f, 0.f,
		coordsRect.val[1][0], coordsRect.val[1][1], 0.f, 0.f,
		coordsRect.val[2][0], coordsRect.val[2][1], 0.f, 1.f,
		coordsRect.val[2][0], coordsRect.val[2][1], 0.f, 1.f,
		coordsRect.val[3][0], coordsRect.val[3][1], 1.f, 1.f,
		coordsRect.val[0][0], coordsRect.val[0][1], 1.f, 0.f,
	};
	genVertexObject();
}
auto genVertexObject() -> void
{
	glGenVertexArray(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(float), &this->rect[0], GL_STATIC_READ);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // end namespace gui

} // end namespace id
