#include "txtLogger.h"
#include "guiMenu.h"
#include "guiRect.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiMenu::~GuiMenu()
{
	logger->log("Deleting GuiMenu...", LL_INFO);

	logger->log("GuiMenu deleted", LL_INFO);
}
auto GuiMenu::createMenuTitleScreen() -> void
{
	
}
auto GuiMenu::deleteMenuTitleScreen() -> void
{

}
GuiMenu::GuiMenu()
{
	logger->log("Creating Menu...", LL_INFO);

	logger->log("Menu created", LL_INFO);
}

} // end namespace gui

} // end namespace id
