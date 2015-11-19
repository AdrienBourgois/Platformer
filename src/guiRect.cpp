#include "guiRect.h"
#include "guiManager.h"
#include "maths/vector.h"

namespace id {
namespace gui {

GuiRect::GuiRect(GuiManager* gui, maths::Vector2 pos, int width, int height)
: pos(pos), width(width), height(height)
{
	gui->addToRender(this);
}
GuiRect::~GuiRect()
{
}

} // end namespace gui

} // end namespace id
