#ifndef GUI_RECT_H_INCLUDED
#define GUI_RECT_H_INCLUDED

#include <GL/gl.h>

#include "maths/vector.h"

namespace id {
namespace gui {

class GuiManager;

class GuiRect
{
public:
	GuiRect(GuiManager* gui, maths::Vector2 pos, int width, int height);
	~GuiRect();

	auto getPosition() const -> maths::Vector2 { return this->pos; };
	auto getColor() const -> maths::Vector4 { return this->color; };
	auto getWidth() const -> int { return this->width; };
	auto getHeight() const -> int { return this->height; };

private:
	maths::Vector2 pos;
	maths::Vector4 color;
	int width;
	int height;
};

} // end namespace gui

} // end namespace id

#endif // GUI_RECT_H_INCLUDED
