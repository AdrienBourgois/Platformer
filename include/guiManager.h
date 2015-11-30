#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include <memory>
#include <vector>

#include "maths/matrix.h"

namespace id {
namespace gui {

class GuiManager
{
public:
	~GuiManager();
	GuiManager(GuiManager const&) = delete;
	GuiManager(GuiManager&&) = delete;
	GuiManager& operator = (GuiManager const&) = delete;
	GuiManager& operator = (GuiManager&&) = delete;

	static auto createGuiManager(int windowWidth, int windowHeight) -> std::unique_ptr<GuiManager>;

private:
	GuiManager(int windowWidth, int windowHeight);

	int windowWidth, windowHeight;
	std::vector<float> camOrtho;
};

} // end namespace gui

} // end namespace id

#endif // GUI_MANAGER_H_INCLUDED
