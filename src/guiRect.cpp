#include <GL/glew.h>
#include <vector>

#include "guiRect.h"
#include "guiManager.h"
#include "maths/vector.h"

#include <iostream>

namespace id {
namespace gui {

GuiRect::GuiRect(GuiManager* gui, maths::Vector4 color)
{
	this->rect =
	{
		500.f, 100.f, color.val[0], color.val[1], color.val[2], color.val[3],
		300.f, 100.f, color.val[0], color.val[1], color.val[2], color.val[3],
		300.f, -100.f, color.val[0], color.val[1], color.val[2], color.val[3],
		300.f, -100.f, color.val[0], color.val[1], color.val[2], color.val[3],
		500.f, -100.f, color.val[0], color.val[1], color.val[2], color.val[3],
		500.f, 100.f, color.val[0], color.val[1], color.val[2], color.val[3],
	};

	this->color = color;

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->rect.size() * sizeof(GLfloat), &this->rect[0], GL_STATIC_READ);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	gui->addToRender(this);
}
GuiRect::~GuiRect()
{
}

} // end namespace gui

} // end namespace id
